const orderBy = require("./orderBy");

describe("orderBy function", () => {
  test("сортирует массив объектов по заданным свойствам", () => {
    const input = [
      { name: "John", age: 25 },
      { name: "Alice", age: 30 },
      { name: "John", age: 20 },
    ];

    const properties = ["name", "age"];

    const expected = [
      { name: "Alice", age: 30 },
      { name: "John", age: 20 },
      { name: "John", age: 25 },
    ];

    expect(orderBy(input, properties)).toEqual(expected);
  });

  test("выбрасывает исключение, если первый аргумент не массив", () => {
    expect(() => orderBy("not an array", ["name"])).toThrow("Первый аргумент должен быть массивом.");
  });

  test("выбрасывает исключение, если элементы массива не объекты", () => {
    const input = [1, 2, 3];
    expect(() => orderBy(input, ["name"])).toThrow("Все элементы массива должны быть объектами.");
  });

  test("выбрасывает исключение, если свойство отсутствует в объекте", () => {
    const input = [
      { name: "John", age: 25 },
      { name: "Alice" },
    ];

    expect(() => orderBy(input, ["name", "age"])).toThrow('Свойство "age" отсутствует в одном из объектов.');
  });

  test("выбрасывает исключение, если второй аргумент не массив строк", () => {
    const input = [{ name: "John" }];
    expect(() => orderBy(input, "not an array")).toThrow("Второй аргумент должен быть массивом строк.");
  });
});