const CONSTANTS = {
    EI: [[3, 3, 4], [3, 4, 6], [4, 6, 6]],
    EO: [[4, 4, 5], [4, 5, 7], [5, 7, 7]],
    ILF: [[7, 7, 10], [7, 10, 15], [10, 15, 15]],
    EIF: [[5, 5, 7], [5, 7, 10], [7, 10, 10]],
    EQ: [[3, 3, 4], [3, 4, 6], [4, 6, 6]],
}

export const formSquareMatrix = (size, initialValue= 0) => {
    const result = [];

    for (let i = 0; i < size; i++) {
        result.push([]);
        for (let j = 0; j < size; j++) {
            result[i][j] = initialValue;
        }
    }

    return result;
}

export const calculateTDI = (characteristics) => {
    let FP = 0;    
    for (let i = 0; i < 3; i++){
        for (let j = 0; j < 3; j++){
            FP += +characteristics.EI[i][j] * CONSTANTS.EI[i][j]
            + +characteristics.EO[i][j] * CONSTANTS.EO[i][j]
            + +characteristics.ILF[i][j] * CONSTANTS.ILF[i][j]
            + +characteristics.EIF[i][j] * CONSTANTS.EIF[i][j]
            + +characteristics.EQ[i][j] * CONSTANTS.EQ[i][j]
        }
    }
    return FP;
}