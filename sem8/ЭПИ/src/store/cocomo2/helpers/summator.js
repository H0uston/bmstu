export const coeffsSummator = (systemParams) => {
    let coeffs = Object.values(systemParams);
    let FP = 0;
    coeffs.forEach(element => {
        FP += +element;
    });
    return FP;
}

// Нормирующий фактор
export const computeVAF = (sumOfCoeffs) => {
    return 0.65 + 0.01 * sumOfCoeffs;
}

// Коэффициент p
export const computeP = (factorsForP) => {
    let factorsValue = Object.values(factorsForP).map(v => +v);
    let sum = 0;
    factorsValue.forEach(element => {
        sum += + element;
    })
    return sum / 100 + 1.01;
}

// Экранные формы
export const computeScreenForms = (data) => {
    return +data.simpleForms + +data.middleForms * 2 + +data.difficultForms * 3;
}

// Отчёты
export const computeDocs = (data) => {
    return +data.simpleReports * 2 + +data.middleReports * 5 + +data.difficultReports * 8;
}

export const computeArch = (data) => {
    let mult = 1;
    let args = Object.values(data);
    args.forEach(element => {
        mult *= element;
    })
    return mult.toFixed(2);
}