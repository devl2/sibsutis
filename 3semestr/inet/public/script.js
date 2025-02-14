class Value {
    constructor(name) {
        this.name = name;
        this.courses = {};
    }

    create(date, buy, sell) {
        this.courses[date] = { buy, sell };
    }

    read(date) {
        return this.courses[date] || null;
    }

    update(date, buy, sell) {
        if (this.courses[date]) {
            this.courses[date] = { buy, sell };
        }
    }

    delete(date) {
        delete this.courses[date];
    }
}

class Type {
    constructor(name) {
        this.name = name;
    }

    update(newName) {
        this.name = newName;
    }
}

class Expense {
    constructor(value, date, currency, type) {
        this.value = value;
        this.date = date;
        this.currency = currency;
        this.type = type;
    }
}

class Income {
    constructor(value, date, currency, type) {
        this.value = value;
        this.date = date;
        this.currency = currency;
        this.type = type;
    }
}

class Budget {
    constructor() {
        this.values = [];
        this.expenseTypes = [];
        this.incomeTypes = [];
        this.expenses = [];
        this.incomes = [];
    }

    addValue(value) {
        this.values.push(value);
    }

    addExpenseType(type) {
        this.expenseTypes.push(type);
    }

    addIncomeType(type) {
        this.incomeTypes.push(type);
    }

    addExpense(expense) {
        this.expenses.push(expense);
    }

    addIncome(income) {
        this.incomes.push(income);
    }

    calculateBalance(startDate, endDate, typeFilter = null) {
        let totalIncome = 0;
        let totalExpense = 0;

        this.incomes.forEach(income => {
            if (income.date >= startDate && income.date <= endDate && (!typeFilter || income.type === typeFilter)) {
                totalIncome += income.value;
            }
        });

        this.expenses.forEach(expense => {
            if (expense.date >= startDate && expense.date <= endDate && (!typeFilter || expense.type === typeFilter)) {
                totalExpense += expense.value;
            }
        });

        return totalIncome - totalExpense;
    }

    filterTransactions(startDate, endDate, typeFilter = null, isIncome = true) {
        const transactions = isIncome ? this.incomes : this.expenses;

        return transactions.filter(transaction => {
            return (
                transaction.date >= startDate &&
                transaction.date <= endDate &&
                (!typeFilter || transaction.type === typeFilter)
            );
        });
    }
}

const ctx = document.getElementById('balanceChart').getContext('2d');
let balanceChart;

    const budget = new Budget();

    async function loadBudgetFromServer() {
        try {
            const response = await fetch("/api/budget");
            if (!response.ok) throw new Error("Ошибка загрузки данных с сервера.");
    
            const budgetData = await response.json();
            console.log("Загруженные данные:", budgetData);
    
            budget.incomes = budgetData.incomes || [];
            budget.expenses = budgetData.expenses || [];

            updateIncomeList();
            updateExpenseList();
            updateBalanceChart();
        } catch (error) {
            console.error("Не удалось загрузить данные бюджета:", error);
        }
    }
    
      async function saveBudgetToServer() {
    const budgetData = {
        incomes: budget.incomes,
        expenses: budget.expenses,
    };

    try {
        const response = await fetch("/api/budget", {
            method: "POST",
            headers: { "Content-Type": "application/json" },
            body: JSON.stringify(budgetData),
        });

        if (!response.ok) {
            throw new Error("Ошибка сохранения данных на сервере.");
        }
        console.log("Данные успешно сохранены.");
    } catch (error) {
        console.error("Ошибка при сохранении данных бюджета:", error);
    }
}
async function saveBudgetToServer() {
    const budgetData = {
        incomes: budget.incomes,
        expenses: budget.expenses,
    };

    try {
        const response = await fetch("/api/budget", {
            method: "POST",
            headers: { "Content-Type": "application/json" },
            body: JSON.stringify(budgetData),
        });

        if (!response.ok) {
            throw new Error("Ошибка сохранения данных на сервере.");
        }
        console.log("Данные успешно сохранены.");
    } catch (error) {
        console.error("Ошибка при сохранении данных бюджета:", error);
    }
}


    const dailyLabels = ['Воскресенье', 'Понедельник', 'Вторник', 'Среда', 'Четверг', 'Пятница', 'Суббота'];
    const monthlyLabels = ['Январь', 'Февраль', 'Март', 'Апрель', 'Май', 'Июнь', 'Июль', 'Август', 'Сентябрь', 'Октябрь', 'Ноябрь', 'Декабрь'];
    const yearlyLabels = ['2021', '2022', '2023', '2024', '2025'];

    let currentPeriod = 'days';
    let selectedCurrency = 'RUB';

    const periodData = {
      days: { labels: dailyLabels, incomeData: Array(dailyLabels.length).fill(0), expenseData: Array(dailyLabels.length).fill(0) },
      months: { labels: monthlyLabels, incomeData: Array(monthlyLabels.length).fill(0), expenseData: Array(monthlyLabels.length).fill(0) },
      years: { labels: yearlyLabels, incomeData: Array(yearlyLabels.length).fill(0), expenseData: Array(yearlyLabels.length).fill(0) }
    };
    
    const exchangeRates = {
      USD: 100,
      EUR: 110,
      RUB: 1,
    };
    
    function convertToRUB(amount, currency) {
      return amount * (exchangeRates[currency] || 1);
    }
    
    function convertToSelectedCurrency(amount, currency) {
      const amountInRUB = amount * exchangeRates[currency];
      return amountInRUB / exchangeRates[selectedCurrency];
    }

    function deleteIncome(index) {
    const income = budget.incomes[index];

    const { dayIndex, monthIndex, yearIndex } = getDateIndices(income.date);

    for (let i = dayIndex; i < periodData.days.incomeData.length; i++) {
            periodData.days.incomeData[i] -= income.value;
        }
        for (let i = monthIndex; i < periodData.months.incomeData.length; i++) {
            periodData.months.incomeData[i] -= income.value;
        }
        for (let i = yearIndex; i < periodData.years.incomeData.length; i++) {
            periodData.years.incomeData[i] -= income.value;
        }

    budget.incomes.splice(index, 1);

    updateIncomeList();
    updateBalanceChart();
    saveBudgetToServer();
  }

  function deleteExpense(index) {
    const expense = budget.expenses[index];

    const { dayIndex, monthIndex, yearIndex } = getDateIndices(expense.date);
    for (let i = dayIndex; i < periodData.days.expenseData.length; i++) {
            periodData.days.expenseData[i] -= expense.value;
        }
        for (let i = monthIndex; i < periodData.months.expenseData.length; i++) {
            periodData.months.expenseData[i] -= expense.value;
        }
        for (let i = yearIndex; i < periodData.years.expenseData.length; i++) {
            periodData.years.expenseData[i] -= expense.value;
        }

    budget.expenses.splice(index, 1);

    updateExpenseList();
    updateBalanceChart();
    saveBudgetToServer();
  }

  function editIncome(index) {
    const income = budget.incomes[index];

    const newAmount = prompt('Введите новую сумму дохода', income.value);
    const newDescription = prompt('Введите новое описание дохода', income.name);
    const newDate = prompt('Введите новую дату дохода (в формате YYYY-MM-DD)', income.date);
    const newType = prompt('Введите новое тип расхода', income.type.name);


    if (newAmount && newDescription && newDate) {
      const { dayIndex: oldDayIndex, monthIndex: oldMonthIndex, yearIndex: oldYearIndex } = getDateIndices(income.date);
      for (let i = oldDayIndex; i < periodData.days.incomeData.length; i++) {
            periodData.days.incomeData[i] -= income.value;
        }
      for (let i = oldMonthIndex; i < periodData.months.incomeData.length; i++) {
            periodData.months.incomeData[i] -= income.value;
        }
      for (let i = oldYearIndex; i < periodData.years.incomeData.length; i++) {
            periodData.years.incomeData[i] -= income.value;
        }
      income.value = parseFloat(newAmount);
      income.name = newDescription;
      income.date = newDate;
      income.type.name = newType;

      const { dayIndex, monthIndex, yearIndex } = getDateIndices(newDate);

      for (let i = dayIndex; i < periodData.days.incomeData.length; i++) {
            periodData.days.incomeData[i] += income.value;
        }
      for (let i = monthIndex; i < periodData.months.incomeData.length; i++) {
            periodData.months.incomeData[i] += income.value;
        }
      for (let i = yearIndex; i < periodData.years.incomeData.length; i++) {
            periodData.years.incomeData[i] += income.value;
        }
    
      updateIncomeList();
      updateBalanceChart();
      saveBudgetToServer();
    }
  }

function editExpense(index) {
  const expense = budget.expenses[index];

  const newAmount = prompt('Введите новую сумму расхода', expense.value);
  const newDescription = prompt('Введите новое описание расхода', expense.name);
  const newDate = prompt('Введите новую дату расхода (в формате YYYY-MM-DD)', expense.date);
  const newType = prompt('Введите новое тип расхода', expense.type.name);

  if (newAmount && newDescription && newDate) {
      const { dayIndex: oldDayIndex, monthIndex: oldMonthIndex, yearIndex: oldYearIndex } = getDateIndices(expense.date);
      for (let i = oldDayIndex; i < periodData.days.expenseData.length; i++) {
            periodData.days.expenseData[i] -= expense.value;
        }
      for (let i = oldMonthIndex; i < periodData.months.expenseData.length; i++) {
            periodData.months.expenseData[i] -= expense.value;
        }
      for (let i = oldYearIndex; i < periodData.years.expenseData.length; i++) {
            periodData.years.expenseData[i] -= expense.value;
        }
        expense.value = parseFloat(newAmount);
        expense.name = newDescription;
        expense.date = newDate;
        expense.type.name = newType;

      const { dayIndex, monthIndex, yearIndex } = getDateIndices(newDate);

      for (let i = dayIndex; i < periodData.days.expenseData.length; i++) {
            periodData.days.expenseData[i] += expense.value;
        }
      for (let i = monthIndex; i < periodData.months.expenseData.length; i++) {
            periodData.months.expenseData[i] += expense.value;
        }
      for (let i = yearIndex; i < periodData.years.expenseData.length; i++) {
            periodData.years.expenseData[i] += expense.value;
        }
    
      updateExpenseList();
      updateBalanceChart();
      saveBudgetToServer();
    }
  }

  function updateBalanceChart() { 
    const data = periodData[currentPeriod];

    data.incomeData.fill(0);
    data.expenseData.fill(0);

    budget.incomes.forEach(income => {
        const { dayIndex, monthIndex, yearIndex } = getDateIndices(income.date);

        if (currentPeriod === 'days') data.incomeData[dayIndex] += income.value;
        if (currentPeriod === 'months') data.incomeData[monthIndex] += income.value;
        if (currentPeriod === 'years') data.incomeData[yearIndex] += income.value;
    });

    budget.expenses.forEach(expense => {
        const { dayIndex, monthIndex, yearIndex } = getDateIndices(expense.date);

        if (currentPeriod === 'days') data.expenseData[dayIndex] += expense.value;
        if (currentPeriod === 'months') data.expenseData[monthIndex] += expense.value;
        if (currentPeriod === 'years') data.expenseData[yearIndex] += expense.value;
    });

    const incomeDataInSelectedCurrency = data.incomeData.map(income =>
        convertToSelectedCurrency(income, 'RUB')
    );
    const expenseDataInSelectedCurrency = data.expenseData.map(expense =>
        convertToSelectedCurrency(expense, 'RUB')
    );

    const balanceData = [];
    let lastKnownBalance = 0;

    for (let i = 0; i < data.labels.length; i++) {
        const income = incomeDataInSelectedCurrency[i];
        const expense = expenseDataInSelectedCurrency[i];

        if (!isNaN(income) && !isNaN(expense)) {
            lastKnownBalance += income - expense;
        }
        balanceData.push(lastKnownBalance);
    }

    budget.balanceData = balanceData;

    if (balanceChart) {
        balanceChart.destroy();
    }

    balanceChart = new Chart(ctx, {
        type: 'line',
        data: {
            labels: data.labels,
            datasets: [{
                label: `Баланс (${selectedCurrency})`,
                data: balanceData,
                fill: false,
                borderColor: 'rgba(75, 192, 192, 1)',
                tension: 0.1
            }]
        },
        options: {
            responsive: true,
            scales: {
                y: {
                    beginAtZero: true,
                    ticks: {
                        callback: function(value) {
                            return value.toFixed(2) + ` ${selectedCurrency}`;
                        }
                    }
                }
            }
        }
    });
}

function getDateIndices(date) {
  const dateObj = new Date(date);
  
  const dayIndex = dateObj.getDay();
  const monthIndex = dateObj.getMonth();
  const yearIndex = dateObj.getFullYear() - 2021;

  return { dayIndex, monthIndex, yearIndex };
}

document.addEventListener('DOMContentLoaded', async () => {
  await loadBudgetFromServer();
  currentPeriod = 'days'; 
  updateBalanceChart();
});

document.getElementById('currencySelect').addEventListener('change', function () {
  selectedCurrency = this.value;
  updateBalanceChart();
});

document.getElementById('addIncomeBtn').addEventListener('click', function () {
  const amount = prompt('Введите сумму дохода:');
  const description = prompt('Введите описание дохода:');
  const date = prompt('Введите дату (в формате YYYY-MM-DD):', new Date().toISOString().split('T')[0]);
  const currency = prompt('Выберите валюту (RUB, USD, EUR):', 'RUB');

  const incomeTypes = ['Зарплата', 'Продажа', 'Проценты', 'Прочее'];
  const incomeType = prompt(`Выберите тип дохода (или введите новый):\n${incomeTypes.join('\n')}`);
  const finalIncomeType = incomeTypes.includes(incomeType) ? incomeType : incomeType || 'Прочее';

  if (amount && description && date && exchangeRates[currency]) {
    const amountInRUB = convertToRUB(parseFloat(amount), currency);
    const income = new Income(amountInRUB, date, 'RUB', new Type(finalIncomeType));

    income.name = description;

    budget.addIncome(income);

    const { dayIndex, monthIndex, yearIndex } = getDateIndices(date);

    for (let i = dayIndex; i < periodData.days.incomeData.length; i++) {
        periodData.days.incomeData[i] += amountInRUB;
    }
    for (let i = monthIndex; i < periodData.months.incomeData.length; i++) {
        periodData.months.incomeData[i] += amountInRUB;
    }
    for (let i = yearIndex; i < periodData.years.incomeData.length; i++) {
        periodData.years.incomeData[i] += amountInRUB;
    }

    updateIncomeList();
    updateBalanceChart();
    saveBudgetToServer();
  }
});

  document.getElementById('addExpenseBtn').addEventListener('click', function () {
    const amount = prompt('Введите сумму расхода:');
    const description = prompt('Введите описание расхода:');
    const date = prompt('Введите дату (в формате YYYY-MM-DD):', new Date().toISOString().split('T')[0]);
    const currency = prompt('Выберите валюту (RUB, USD, EUR):', 'RUB');

    const expenseTypes = ['Продукты', 'Транспорт', 'Жилье', 'Прочее'];

    const expenseType = prompt(`Выберите тип расхода (или введите новый):\n${expenseTypes.join('\n')}`);
    const finalExpenseType = expenseTypes.includes(expenseType) ? expenseType : expenseType || 'Прочее';

    if (amount && description && date && exchangeRates[currency]) {
        const amountInRUB = convertToRUB(parseFloat(amount), currency);
        const expense = new Expense(amountInRUB, date, 'RUB', new Type(finalExpenseType));

        expense.name = description;

        budget.addExpense(expense);

        const { dayIndex, monthIndex, yearIndex } = getDateIndices(date);

        for (let i = dayIndex; i < periodData.days.expenseData.length; i++) {
            periodData.days.expenseData[i] += amountInRUB;
        }
        for (let i = monthIndex; i < periodData.months.expenseData.length; i++) {
            periodData.months.expenseData[i] += amountInRUB;
        }
        for (let i = yearIndex; i < periodData.years.expenseData.length; i++) {
            periodData.years.expenseData[i] += amountInRUB;
        }

        updateExpenseList();  
        updateBalanceChart();
        saveBudgetToServer();
    }
  });


document.getElementById('incomeTypeFilter').addEventListener('change', function () {
  updateIncomeList();
});

document.getElementById('expenseTypeFilter').addEventListener('change', function () {
  updateExpenseList();
});

function updateIncomeList() {
    const incomeList = document.getElementById('incomeList');
    incomeList.innerHTML = '';
    let totalInRUB = 0;

    const filterType = document.getElementById('incomeTypeFilter').value;

    if (budget.incomes.length === 0) {
        incomeList.innerHTML = '<li class="list-group-item">Нет доходов</li>';
        return;
    }

    budget.incomes.forEach((income, index) => {
        if (filterType === '' || income.type.name === filterType) {
            const listItem = document.createElement('li');
            listItem.className = 'list-group-item d-flex justify-content-between align-items-center';
            const incomeInRUB = convertToRUB(income.value, income.currency);
            totalInRUB += incomeInRUB;

            listItem.textContent = `${income.name} (${income.type.name}): ${incomeInRUB.toFixed(2)} RUB (${income.date})`;

            const editButton = document.createElement('button');
            editButton.className = 'btn btn-sm btn-warning';
            editButton.textContent = 'Редактировать';
            editButton.onclick = () => editIncome(index);
            listItem.appendChild(editButton);

            const deleteButton = document.createElement('button');
            deleteButton.className = 'btn btn-sm btn-danger ms-2';
            deleteButton.textContent = 'Удалить';
            deleteButton.onclick = () => deleteIncome(index);
            listItem.appendChild(deleteButton);

            incomeList.appendChild(listItem);
        }
    });

    const totalItem = document.createElement('li');
    totalItem.className = 'list-group-item active';
    totalItem.textContent = `Итого: ${totalInRUB.toFixed(2)} RUB`;
    incomeList.appendChild(totalItem);

}


function updateExpenseList() {
    const expenseList = document.getElementById('expenseList');
    expenseList.innerHTML = '';
    let totalInRUB = 0;

    const filterType = document.getElementById('expenseTypeFilter').value;

    if (budget.expenses.length === 0) {
      expenseList.innerHTML = '<li class="list-group-item">Нет расходов</li>';
    }

    budget.expenses.forEach((expense, index) => {
        if (filterType === '' || expense.type.name === filterType) {
            const listItem = document.createElement('li');
            listItem.className = 'list-group-item d-flex justify-content-between align-items-center';
            const expenseInRUB = convertToRUB(expense.value, expense.currency);
            totalInRUB += expenseInRUB;

            listItem.textContent = `${expense.name} (${expense.type.name}): ${expenseInRUB.toFixed(2)} RUB (${expense.date})`;

            const editButton = document.createElement('button');
            editButton.className = 'btn btn-sm btn-warning';
            editButton.textContent = 'Редактировать';
            editButton.onclick = () => editExpense(index);
            listItem.appendChild(editButton);

            const deleteButton = document.createElement('button');
            deleteButton.className = 'btn btn-sm btn-danger ms-2';
            deleteButton.textContent = 'Удалить';
            deleteButton.onclick = () => deleteExpense(index);
            listItem.appendChild(deleteButton);

            expenseList.appendChild(listItem);
        }
    });


    const totalItem = document.createElement('li');
    totalItem.className = 'list-group-item active';
    totalItem.textContent = `Итого: ${totalInRUB.toFixed(2)} RUB`;
    expenseList.appendChild(totalItem);

}


document.getElementById('balanceBtn').addEventListener('click', function () {
  currentPeriod = 'days';
  document.getElementById('balancePage').classList.remove('d-none');
  document.getElementById('incomePage').classList.add('d-none');
  document.getElementById('expensePage').classList.add('d-none');
  document.getElementById('addIncomeBtn').classList.add('d-none');
  document.getElementById('addExpenseBtn').classList.add('d-none');
  document.getElementById('incomeTypeFilter').classList.add('d-none');
  document.getElementById('expenseTypeFilter').classList.add('d-none');
  document.getElementById('settingsPage').classList.add('d-none');
  updateBalanceChart();
});

document.getElementById('incomeBtn').addEventListener('click', function () {
  document.getElementById('incomePage').classList.remove('d-none');
  document.getElementById('balancePage').classList.add('d-none');
  document.getElementById('expensePage').classList.add('d-none');
  document.getElementById('addIncomeBtn').classList.remove('d-none');
  document.getElementById('addExpenseBtn').classList.add('d-none');
  document.getElementById('incomeTypeFilter').classList.remove('d-none');
  document.getElementById('expenseTypeFilter').classList.add('d-none');
  document.getElementById('settingsPage').classList.add('d-none');
  updateBalanceChart();
});

document.getElementById('expenseBtn').addEventListener('click', function () {
  document.getElementById('expensePage').classList.remove('d-none');
  document.getElementById('balancePage').classList.add('d-none');
  document.getElementById('incomePage').classList.add('d-none');
  document.getElementById('addIncomeBtn').classList.add('d-none');
  document.getElementById('addExpenseBtn').classList.remove('d-none');
  document.getElementById('incomeTypeFilter').classList.add('d-none');
  document.getElementById('expenseTypeFilter').classList.remove('d-none');
  document.getElementById('settingsPage').classList.add('d-none');
  updateBalanceChart();
});

document.getElementById('settingsBtn').addEventListener('click', function () {
  document.getElementById('settingsPage').classList.remove('d-none');
  document.getElementById('balancePage').classList.add('d-none');
  document.getElementById('incomePage').classList.add('d-none');
  document.getElementById('expensePage').classList.add('d-none');
  document.getElementById('addIncomeBtn').classList.add('d-none');
  document.getElementById('addExpenseBtn').classList.add('d-none');
  document.getElementById('incomeTypeFilter').classList.add('d-none');
  document.getElementById('expenseTypeFilter').classList.add('d-none');
});


document.querySelectorAll('[data-period]').forEach(item => {
  item.addEventListener('click', function () {
    currentPeriod = this.getAttribute('data-period');
    updateBalanceChart();
  });
});

updateIncomeList();
updateExpenseList();


