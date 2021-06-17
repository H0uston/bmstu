export const computeTotal = (array) => {
    return array.reduce((a, b) => parseInt(a) + parseInt(b), 0);
};

export const formDecomposition = ({ title, budget }) => {
    const result = [];
    let sum = 0;

    for (let key in budget) {
        sum += budget[key];
    }

    for (let key in budget) {
        const postfix = `(${(budget[key] / sum * 100).toFixed(0)}%)`
        result.push(
            { name: title[key] + postfix, value: +(budget[key].toFixed(2))}
        );
    }


    return result;
}

export const formDistribution = ({ title, work, time}) => {
    const workResult = [];
    const timeResult = [];

    for (let key in work) {
        workResult.push(
            { name: title[key], value: +(work[key].toFixed(2))}
        );
        timeResult.push(
            { name: title[key], value: +(time[key].toFixed(2))}
        );
    }

    return { 'work': workResult, 'time': timeResult };
}

export const formDiagram = ({ title, dataWt}) => {
    const diagram = [];

    for (let key in dataWt) {
        diagram.push(
            { name: title[key], value: Math.ceil(dataWt[key]) }
        )
    }

    return diagram;
};
