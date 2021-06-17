export const UPDATE_SYSTEM_PARAMS = 'UPDATE-SYSTEM-PARAMS';

export const UPDATE_CHARACTERISTICS = 'UPDATE-CHARACTERISTICS';

export const UPDATE_POWER = 'UPDATE-POWER';

export const UPDATE_COMPOSITIONAL = 'UPDATE-COMPOSITIONAL';

export const UPDATE_EARLY_DEVELOPMENT = 'UPDATE-EARLY-DEVELOPMENT';

export const UPDATE_LANGUAGE = 'UPDATE-LANGUAGE';

export const COMPUTE_FUNCTIONAL_POINTS = 'COMPUTE-FUNCTIONAL-POINTS';

export const COMPUTE_COMPOSITIONAL = 'COMPUTE-COMPOSITIONAL';

export const COMPUTE_EARLY_DEVELOPMENT = 'COMPUTE-EARLY-DEVELOPMENT';

export const updateSystemParamsAction = ({name, value}) => ({
    type: UPDATE_SYSTEM_PARAMS,
    payload: { name, value},
});


export const updateCharacteristicsAction = ({name, position: {row, column}, value}) => ({
    type: UPDATE_CHARACTERISTICS,
    payload: { name, position: {row, column}, value },
});

export const computeFunctionalPointsAction = () => ({
    type: COMPUTE_FUNCTIONAL_POINTS,
});

export const updatePowerAction = ({name, newValue}) => ({
    type: UPDATE_POWER,
    payload: {name, newValue},
});

export const updateCompositionalAction = ({name, newValue}) => ({
    type: UPDATE_COMPOSITIONAL,
    payload: {name, newValue},
});

export const updateEarlyDevelopmentAction = ({name, newValue}) => ({
    type: UPDATE_EARLY_DEVELOPMENT,
    payload: {name, newValue},
});

export const updateLanguageAction = ({ name, newValue}) => ({
    type: UPDATE_LANGUAGE,
    payload: {name, newValue},
});

export const computeCompositionalAction = () => ({
    type: COMPUTE_COMPOSITIONAL,
});

export const computeEarlyDevelopmentAction = () => ({
    type: COMPUTE_EARLY_DEVELOPMENT,
});
