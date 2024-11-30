class Value{
    constructor(name){
        this.name = name;
        this.course = [];
    }

    create(date, buy, sell) {
        this.course[date] = { buy, sell };
    }

    read(date) {
        return this.course[date];
    }

    update(date, buy, sell){
        if(this.course[date]){
            this.course[date] = { buy, sell };
        }
    }

    delete(name){
       delete this.course[name];
    }
}

class Course{
    constructor(buy, sell, date){
        this.buy = buy;
        this.sell = sell;
        this.date = date;
    }

    create(date, buy, sell) {
        this.rates[date] = { buy, sell };
    }

    read(date) {
        return this.rates[date];
    }

    update(date, buy, sell){
        if(this.rates[date]){
            this.rates[date] = {buy, sell};
        }
    }

    delete(date){
       delete this.rates[date];
    }
}

class TypeRas{
    constructor(name){
        this.name = name;
    }

    create(name) {
        this.typeRas[name] = name;
    }

    read(name) {
        return this.typeRas[name];
    }

    update(name){
        if(this.typeRas[name]){
            this.typeRas[name] = name;
        }
    }

    delete(name){
       delete this.typeRas[name];
    }
}

class TypeDoxod{
    constructor(name){
        this.name = name;
    }

    create(name) {
        this.TypeDoxod[name] = name;
    }

    read(name) {
        return this.TypeDoxod[name];
    }

    update(name){
        if(this.TypeDoxod[name]){
            this.TypeDoxod[name] = name;
        }
    }

    delete(name){
       delete this.TypeDoxod[name];
    }
}

class Ras{
    constructor(data, typeRas, date, value){
        this.data = data;
        this.typeRas = typeRas;
        this.date = date;
        this.value = value;
    }
}

class Doxod{
    constructor(data, TypeDoxod, date, value){
        this.data = data;
        this.TypeDoxod = TypeDoxod;
        this.date = date;
        this.value = value;
    }
}

class Budget{
    constructor(){
        this.Value = [];
        this.TypeRas = [];
        this.TypeDoxod = [];
        this.Doxod = [];
        this.Ras = [];
    }
}

let usdt = new Value('usdt');
let rub = new Value('rub');

let test = new TypeRas('salfetka');

usdt.create('12.11.2024', 75, 99);
usdt.create('15.11.2024', 110, 669);
rub.create('15.11.2024', 10, 12);

test.create('salfetka2');
test.delete('salfetka2');

console.log(usdt);
console.log(usdt.read('15.11.2024'));
console.log(rub.read('15.11.2024'));
