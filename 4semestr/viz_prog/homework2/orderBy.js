function orderBy(array, properties) {
  if (!Array.isArray(array)) {
    throw new Error("Первый аргумент должен быть массивом.");
  }

  if (!array.every(item => typeof item === "object" && item !== null && !Array.isArray(item))) {
    throw new Error("Все элементы массива должны быть объектами.");
  }

  if (!Array.isArray(properties) || !properties.every(prop => typeof prop === "string")) {
    throw new Error("Второй аргумент должен быть массивом строк.");
  }

  for (const item of array) {
    for (const prop of properties) {
      if (!(prop in item)) {
        throw new Error(`Свойство "${prop}" отсутствует в одном из объектов.`);
      }
    }
  }

  const sortedArray = [...array];

  sortedArray.sort((a, b) => {
    for (const prop of properties) {
      if (a[prop] < b[prop]) return -1;
      if (a[prop] > b[prop]) return 1;
    }
    return 0;
  });

  return sortedArray;
}

module.exports = orderBy;