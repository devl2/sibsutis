// loadData.js
async function loadData() {
    const url = "https://catfact.ninja/breeds";
    let allData = [];
    let currentPage = 1;
    let totalPages = 1;
  
    do {
      const response = await fetch(`${url}?page=${currentPage}`);
      const data = await response.json();
      allData = allData.concat(data.data);
      totalPages = data.last_page;
      currentPage++;
    } while (currentPage <= totalPages);
  
    return allData;
  }
  
  module.exports = loadData; // Экспортируем функцию напрямую