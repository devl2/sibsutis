const express = require('express');
const bodyParser = require('body-parser');
const fs = require('fs');
const crypto = require('crypto');

const app = express();
const PORT = 3000;

const DATA_FILE = 'D:/solutions/inet/budget.json';

app.use(bodyParser.json());
app.use((req, res, next) => {
    res.setHeader('Access-Control-Allow-Origin', '*');
    res.setHeader('Access-Control-Allow-Methods', 'GET, POST, PUT, DELETE, OPTIONS');
    res.setHeader('Access-Control-Allow-Headers', 'Content-Type');
    next();
});

app.use(express.static('D:/solutions/inet/public'));

const readData = () => {
    try {
        if (!fs.existsSync(DATA_FILE)) {
            fs.writeFileSync(DATA_FILE, JSON.stringify({ incomes: [], expenses: [] }, null, 2));
        }
        const rawData = fs.readFileSync(DATA_FILE, 'utf-8');
        return JSON.parse(rawData);
    } catch (error) {
        console.error('Ошибка при чтении данных:', error);
        return { incomes: [], expenses: [] };
    }
};

const writeData = (data) => {
    try {
        fs.writeFileSync(DATA_FILE, JSON.stringify(data, null, 2));
        console.log('Данные успешно сохранены в файл.');
    } catch (error) {
        console.error('Ошибка при сохранении данных:', error);
    }
};

const generateHash = (entry) => {
    const hash = crypto.createHash('sha256');
    hash.update(`${entry.value}-${entry.date}-${entry.type}`);
    return hash.digest('hex');
};

app.get('/api/budget', (req, res) => {
    try {
        const data = readData();
        res.json(data);
    } catch (error) {
        console.error('Ошибка при обработке GET-запроса:', error);
        res.status(500).json({ message: 'Ошибка при чтении данных', error });
    }
});

app.post('/api/budget', (req, res) => {
    try {
        const newData = req.body;

        if (!newData || !Array.isArray(newData.incomes) || !Array.isArray(newData.expenses)) {
            return res.status(400).json({ message: 'Неверный формат данных' });
        }

        const currentData = readData();

        const finalIncomes = newData.incomes.map(income => {
            if (!income.id) {
                income.id = crypto.randomUUID();
            }
            return income;
        });

        const finalExpenses = newData.expenses.map(expense => {
            if (!expense.id) {
                expense.id = crypto.randomUUID();
            }
            return expense;
        });

        const updatedData = { incomes: finalIncomes, expenses: finalExpenses };

        writeData(updatedData);

        res.status(200).json({ message: 'Данные успешно обновлены', data: updatedData });
    } catch (error) {
        console.error('Ошибка при обработке POST-запроса:', error);
        res.status(500).json({ message: 'Ошибка при сохранении данных', error });
    }
});



app.delete('/api/budget/:type/:id', (req, res) => {
    try {
        const { type, id } = req.params;
        const data = readData();

        if (!['incomes', 'expenses'].includes(type)) {
            return res.status(400).json({ message: 'Неверный тип данных' });
        }

        const updatedData = {
            incomes: type === 'incomes' ? data.incomes.filter(item => item.id !== id) : data.incomes,
            expenses: type === 'expenses' ? data.expenses.filter(item => item.id !== id) : data.expenses,
        };

        writeData(updatedData);

        res.status(200).json({ message: `Запись с id ${id} успешно удалена из ${type}` });
    } catch (error) {
        console.error('Ошибка при обработке DELETE-запроса:', error);
        res.status(500).json({ message: 'Ошибка при удалении данных', error });
    }
});


app.listen(PORT, (error) => {
    if (error) {
        console.error(`Ошибка при запуске сервера на порту ${PORT}:`, error);
    } else {
        console.log(`Сервер запущен на http://localhost:${PORT}`);
    }
});
