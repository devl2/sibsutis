function calcStats(catsInfo) {
    const stats = {};
  
    catsInfo.forEach((cat) => {
      const country = cat.country;
      if (!stats[country]) { 
        stats[country] = 0;
      }
      stats[country]++;
    });
  
    return stats;
  }
  
  module.exports = { calcStats };