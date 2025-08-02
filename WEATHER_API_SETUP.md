# Weather API Setup

## OpenWeatherMap API Key

The web interface weather features require an OpenWeatherMap API key.

### Getting API Key:

1. **Registration**: Go to https://openweathermap.org/api
2. **Free account**: Create a free account
3. **API key**: Find your key in the "API keys" section

### API Key Configuration:

#### If using embedded version:
1. Open: `ui/scripts/weather.js`
2. Find: `const apiKey = 'YOUR_API_KEY';`
3. Replace `YOUR_API_KEY` with your actual key
4. Run: `tools/generate_web_resources.py`
5. Upload the sketch

#### If using SPIFFS version:
1. Open: `ui/scripts/weather.js` and `climatecontrol/data/scripts/weather.js`
2. In both files: `const apiKey = 'YOUR_API_KEY';`
3. Replace `YOUR_API_KEY` with your actual key
4. Upload SPIFFS data: Tools > ESP8266 Sketch Data Upload

### Example:
```javascript
const apiKey = 'abc123def456ghi789jkl012mno345pq';
```

### Security Warning:
- ⚠️ **Don't commit real API key to Git repository!**
- 🔒 **Use environment variables or separate config file**
- 📝 **Free API key limit: 1000 calls/month**

### Optional: Operation without API key
If you don't want to use weather features:
- Leave API key as `YOUR_API_KEY`
- All other web interface functions will work
- Only weather effects won't be displayed
