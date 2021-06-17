export const getValuesFromState = (state) => {
    const result = {
        power: {},
        compositional: {},
        earlyDevelopment: {},
        languages: {},
    };

    const {
        models,
        power,
        languages,
    } = state.ccm2;

    for (let key in power) {
        const currentValue = power[key].currentValue;
        result.power[key] = power[key].options[currentValue];
    }

    for (let key in models.compositional) {
        if (key === 'teamCap') {
            const currentValue = models.compositional[key].currentValue;
            result.compositional[key] = models.compositional[key].options[currentValue];
        } else {
            result.compositional[key] = models.compositional[key];
        }
    }

    for (let key in models.earlyDevelopment) {
        const currentValue = models.earlyDevelopment[key].currentValue;
        result.earlyDevelopment[key] = models.earlyDevelopment[key].options[currentValue];
    }

    for (let key in languages) {
        if (+languages[key].value !== 0) {
            result.languages[key] = +languages[key].value * +languages[key].koef;
        }
    }

    result.FP = state.fp.result.countOfFunctionalPoints;

    return result;
}