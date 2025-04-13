import React, { useState, useEffect } from 'react';
import './App.css';

const apiKey = 'eace8a3bb8b53ca12e2ab468f9a5a2ab';

function App() {
  const [weatherData, setWeatherData] = useState(null);
  const [city, setCity] = useState('Novosibirsk');
  const [theme, setTheme] = useState('light');

  const currentDate = new Date();
  const dayOfWeek = currentDate.toLocaleDateString('ru-RU', { weekday: 'long' });
  const dayOfMonth = currentDate.toLocaleDateString('ru-RU', { day: 'numeric' });

  useEffect(() => {
    const fetchWeather = async () => {
      const response = await fetch(`https://api.openweathermap.org/data/2.5/forecast?q=${city}&appid=${apiKey}&units=metric`);
      const data = await response.json();
      setWeatherData(data);
    };

    fetchWeather();
    const interval = setInterval(fetchWeather, 10800000);

    return () => clearInterval(interval);
  }, [city]);

  if (!weatherData) {
    return <div>Loading...</div>;
  }

  const currentWeather = weatherData.list[1];
  const hourlyForecast = weatherData.list.slice(2, 7);

  const dailyForecast = weatherData.list.reduce((acc, forecast) => {
    const date = forecast.dt_txt.split(' ')[0];
    if (!acc[date]) {
      acc[date] = forecast;
    }
    return acc;
  }, {});

  const toggleTheme = () => {
    setTheme(theme === 'light' ? 'dark' : 'light');
  };

  return (
    <div className={`App ${theme}`}>
      <button onClick={toggleTheme} className="theme-toggle">
        Поменять тему
      </button>
      <p className="date">{dayOfWeek}, {dayOfMonth}</p>
      <div className="selector"><CitySelector setCity={setCity} /></div>

      {/* Текущая погода */}
      <div className="current-weather">
      <div className="weather-info">
        <h2 className="city">{weatherData.city.name}</h2>
        <p className="temperature">{Math.round(currentWeather.main.temp)}°C</p>
      </div>
      <img
        src={`http://openweathermap.org/img/wn/${currentWeather.weather[0].icon}@2x.png`}
        alt="weather-icon"
        className="weather-icon-current"
      />
    </div>

      {/* Прогноз на ближайшие часы */}
      <div className="hourly-forecast">
        <div className="hourly-cards">
          {hourlyForecast.map((forecast, index) => (
            <div key={index} className="hourly-card">
              <p>{forecast.dt_txt.split(' ')[1].slice(0, 5)}</p>
              <p className='temperature1'>{Math.round(forecast.main.temp)}°C</p>
              <img
                src={`http://openweathermap.org/img/wn/${forecast.weather[0].icon}@2x.png`}
                alt="weather-icon"
                className="weather-icon"
              />
            </div>
          ))}
        </div>
      </div>

      {/* Более подробный прогноз */}
      <div className="current-weather-more">
      <p>Влажность: 
          <p className='temperature1'>
            {currentWeather.main.humidity}%
            </p>
          </p>
        <p>Скорость ветра: 
          <p className='temperature1'>
            {currentWeather.wind.speed} m/s
          </p>
        </p>
        <p>Давление воздуха
          <p className='temperature1'>
            {weatherData.list[0].main.pressure} mm;
          </p>
        </p>
      </div>

      {/* Прогноз на неделю */}
      <div className="daily-forecast">
        <div className="daily-cards">
          {Object.values(dailyForecast).map((forecast, index) => (
            <div key={index} className="daily-card">
              <p>{new Date(forecast.dt_txt).toLocaleDateString('ru-RU', { weekday: 'long', day: 'numeric' })}</p>
              <img
                src={`http://openweathermap.org/img/wn/${forecast.weather[0].icon}@2x.png`}
                alt="weather-icon"
                className="weather-icon"
              />
              <p className='temperature1'>{Math.round(forecast.main.temp)}°C</p>
            </div>
          ))}
        </div>
      </div>
    </div>
  );
}

function CitySelector({ setCity }) {
  const [inputCity, setInputCity] = useState('');

  const handleSubmit = (e) => {
    e.preventDefault();
    setCity(inputCity);
  };

  return (
    <form onSubmit={handleSubmit}>
      <input className='text'
        type="text"
        value={inputCity}
        onChange={(e) => setInputCity(e.target.value)}
        placeholder="Введите город"
      />
      <button type="submit" className='search'>
        Поиск
      </button>
    </form>
  );
}

export default App;