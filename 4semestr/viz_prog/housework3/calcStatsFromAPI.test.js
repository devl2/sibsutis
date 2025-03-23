// calcStatsFromAPI.test.js
const { calcStatsFromAPI } = require('./calcStatsFromAPI');
const loadData = require('./loadData'); // Импортируем функцию напрямую

// Мокаем модуль loadData
jest.mock('./loadData', () => {
  return jest.fn(() => {
    return Promise.resolve([
      {
        breed: 'Turkish Van',
        country: 'developed in the United Kingdom (founding stock from Turkey)',
        origin: 'Natural',
        coat: 'Semi-long',
        pattern: 'Van',
      },
      {
        breed: 'York Chocolate',
        country: 'United States (New York)',
        origin: 'Natural',
        coat: 'Long',
        pattern: 'Solid',
      },
    ]);
  });
});

describe('calcStatsFromAPI', () => {
  it('должна возвращать корректную статистику', async () => {
    const stats = await calcStatsFromAPI();

    // Проверяем, что функция loadData была вызвана один раз
    expect(loadData).toHaveBeenCalledTimes(1);

    // Проверяем результат
    expect(stats).toEqual({
      'developed in the United Kingdom (founding stock from Turkey)': 1,
      'United States (New York)': 1,
    });
  });
});