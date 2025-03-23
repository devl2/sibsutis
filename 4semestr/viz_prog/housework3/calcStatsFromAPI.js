// calcStatsFromAPI.js
const loadData = require('./loadData'); // Импортируем функцию напрямую
const { calcStats } = require('./calcStats');

async function calcStatsFromAPI() {
  const catsInfo = await loadData();
  return calcStats(catsInfo);
}

module.exports = { calcStatsFromAPI };