import express from 'express';
import bodyParser from 'body-parser';
import axios from 'axios';

const app = express();
app.use(bodyParser.json());

// Az Arduino IP-címét itt add meg
const ARDUINO_BASE_URL = 'http://192.168.1.56'; // <-- módosítsd a saját eszközöd IP-jére

// Google Smart Home SYNC endpoint
app.post('/smarthome', async (req, res) => {
  const intent = req.body.inputs?.[0]?.intent;
  switch (intent) {
    case 'action.devices.SYNC':
      return res.json({
        requestId: req.body.requestId,
        payload: {
          agentUserId: 'user-1',
          devices: [
            {
              id: 'chigo-ac',
              type: 'action.devices.types.THERMOSTAT',
              traits: [
                'action.devices.traits.OnOff',
                'action.devices.traits.TemperatureSetting',
                'action.devices.traits.FanSpeed',
                'action.devices.traits.Mode'
              ],
              name: {
                name: 'Chigo Klíma'
              },
              willReportState: false,
              attributes: {
                availableFanSpeeds: {
                  speeds: [
                    { speed_name: 'low', speed_values: [{ speed_synonym: ['alacsony'], lang: 'hu' }] },
                    { speed_name: 'medium', speed_values: [{ speed_synonym: ['közepes'], lang: 'hu' }] },
                    { speed_name: 'high', speed_values: [{ speed_synonym: ['magas'], lang: 'hu' }] }
                  ],
                  ordered: true
                },
                availableModes: {
                  modes: [
                    { mode_name: 'cool', mode_values: [{ mode_synonym: ['hűtés'], lang: 'hu' }] },
                    { mode_name: 'heat', mode_values: [{ mode_synonym: ['fűtés'], lang: 'hu' }] },
                    { mode_name: 'fan_only', mode_values: [{ mode_synonym: ['ventilátor'], lang: 'hu' }] }
                  ]
                },
                thermostatTemperatureUnit: 'C'
              }
            }
          ]
        }
      });
    case 'action.devices.QUERY':
      try {
        const status = await axios.get(`${ARDUINO_BASE_URL}/status`);
        return res.json({
          requestId: req.body.requestId,
          payload: {
            devices: {
              'chigo-ac': {
                on: status.data.power === 'on',
                online: true,
                thermostatMode: status.data.mode,
                thermostatTemperatureSetpoint: status.data.setpoint,
                thermostatTemperatureAmbient: status.data.ambient,
                fanSpeed: status.data.fan
              }
            }
          }
        });
      } catch (e) {
        return res.status(500).json({ error: 'Device unreachable' });
      }
    case 'action.devices.EXECUTE':
      const command = req.body.inputs?.[0]?.payload?.commands?.[0];
      let result = { success: false };
      try {
        for (const exec of command.execution) {
          switch (exec.command) {
            case 'action.devices.commands.OnOff':
              await axios.get(`${ARDUINO_BASE_URL}/${exec.params.on ? 'on' : 'off'}`);
              result.success = true;
              break;
            case 'action.devices.commands.SetTemperature':
              await axios.get(`${ARDUINO_BASE_URL}/set?value=${exec.params.temperature}`);
              result.success = true;
              break;
            case 'action.devices.commands.SetFanSpeed':
              await axios.get(`${ARDUINO_BASE_URL}/setfan?value=${exec.params.fanSpeed}`);
              result.success = true;
              break;
            case 'action.devices.commands.SetMode':
              await axios.get(`${ARDUINO_BASE_URL}/setmode?value=${exec.params.mode}`);
              result.success = true;
              break;
          }
        }
        return res.json({
          requestId: req.body.requestId,
          payload: {
            commands: [
              {
                ids: ['chigo-ac'],
                status: result.success ? 'SUCCESS' : 'ERROR',
                states: { online: true }
              }
            ]
          }
        });
      } catch (e) {
        return res.status(500).json({ error: 'Execution failed' });
      }
    default:
      return res.status(400).json({ error: 'Unknown intent' });
  }
});

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
  console.log(`Smart Home fulfillment server running on port ${PORT}`);
});
