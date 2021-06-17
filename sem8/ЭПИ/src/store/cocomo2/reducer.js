import {calculateTDI, formSquareMatrix} from "./helpers/matrix";
import {
    COMPUTE_COMPOSITIONAL,
    COMPUTE_EARLY_DEVELOPMENT,
    COMPUTE_FUNCTIONAL_POINTS,
    computeCompositionalAction,
    computeEarlyDevelopmentAction,
    computeFunctionalPointsAction,
    UPDATE_CHARACTERISTICS,
    UPDATE_COMPOSITIONAL,
    UPDATE_EARLY_DEVELOPMENT,
    UPDATE_LANGUAGE,
    UPDATE_POWER,
    UPDATE_SYSTEM_PARAMS,
    updateCharacteristicsAction,
    updateCompositionalAction,
    updateEarlyDevelopmentAction,
    updateLanguageAction,
    updatePowerAction,
    updateSystemParamsAction
} from "./actions";
import {minAndMaxValidatorCreator} from "./helpers/validators";
import { coeffsSummator, computeP, computeScreenForms, computeDocs, computeArch, computeVAF, getP } from "./helpers/summator";
import {FCIL, PDIF, PERS, PREX, RCPX, RUSE, teamCap, SCED, PREC, FLEX, RESL, TEAM, PMAT} from './constants';
import {getValuesFromState} from "./helpers/getters";

const initialState = {
    fp: {
        systemParams: {
            dataTransfer: 0,
            distributedDataProcessing: 0,
            performance: 0,
            operationalLimitations: 0,
            transactionFrequency: 0,
            promptDataEntry: 0,
            endUserEfficiency: 0,
            operationalUpdate: 0,
            complexityOfProcessing: 0,
            reusability: 0,
            easeOfInstallation: 0,
            easeOfUse: 0,
            numOfPossInstallsOnPlats: 0,
            flexibility: 0,
        },
        characteristics: {
            EI: formSquareMatrix(3),
            EO: formSquareMatrix(3),
            ILF: formSquareMatrix(3),
            EIF: formSquareMatrix(3),
            EQ: formSquareMatrix(3),
        },
        result: {
            isResultComputed: false,
            sumOfSystemParams: 0,
            countOfFunctionalPoints: 0,
            countOfCorrectedFunctionalPoints: 0,
            normFactor: 0,
        }
    },
    ccm2: {
        models: {
            compositional: {
                RUSE: 10,
                teamCap,
                simpleForms: 0,
                middleForms: 0,
                difficultForms: 0,
                simpleReports: 0,
                middleReports: 0,
                difficultReports: 0,
                countOfModules: 0,
            },
            earlyDevelopment: {
                PERS,
                RCPX,
                RUSE,
                PDIF,
                PREX,
                FCIL,
                SCED,
            }
        },
        power: {
            PREC,
            FLEX,
            RESL,
            TEAM,
            PMAT,
        },
        languages: {
            Assembler: {
                value: 100,
                koef: 320,
            },
            C: {
                value: 0,
                koef: 128,
            },
            Kobol: {
                value: 0,
                koef: 106,
            },
            Fortran: {
                value: 0,
                koef: 106,
            },
            Pascal: {
                value: 0,
                koef: 90,
            },
            'C++': {
                value: 0,
                koef: 53,
            },
            'Java/C#': {
                value: 0,
                koef: 53,
            },
            'Ada 95': {
                value: 0,
                koef: 49,
            },
            'Visual Basic 6': {
                value: 0,
                koef: 24,
            },
            'Visual C++': {
                value: 0,
                koef: 34,
            },
            'Delphi Pascal': {
                value: 0,
                koef: 29,
            },
            Perl: {
                value: 0,
                koef: 21,
            },
            Prolog: {
                value: 0,
                koef: 54,
            },
            SQL: {
                value: 0,
                koef: 21,
            },
            JavaScript: {
                value: 0,
                koef: 47,
            },
        },
        result: {
            isPComputed: false,
            p: 0,
            compositional: {
                isResultComputed: false,
                work: 0,
                time: 0,
                dataWT: [],
            },
            earlyDevelopment: {
                isResultComputed: false,
                work: 0,
                time: 0,
                dataWT: [],
                kLOC: 0
            },
        }
    }
}

const validateMinAndMaxValue = minAndMaxValidatorCreator(0, 5);

const updateSystemParamsCase = (state, payload) => {
    const { name, value } = payload;

    if (isNaN(+value)) {
        return state;
    }

    const validatedValue = validateMinAndMaxValue(value);

    state.fp = { ...state.fp };
    state.fp.systemParams = { ...state.fp.systemParams };

    state.fp.systemParams[name] = +validatedValue;

    return state;
}

const updateCharacteristicsCase = (state, payload) => {
    const { name, position: {row, column}, value } = payload;

    if (isNaN(+value)) {
        return state;
    }

    state.fp.characteristics = { ...state.fp.characteristics };
    state.fp.characteristics[name] = [...state.fp.characteristics[name]];
    state.fp.characteristics[name][row] = [...state.fp.characteristics[name][row]];

    state.fp.characteristics[name][row][column] = +value;

    return state;
}

const computeFunctionalPointsCase = (state) => {
    let sumOfCoeffs = coeffsSummator(state.fp.systemParams);
    let FP = calculateTDI(state.fp.characteristics);

    // Нормирующий фактор VAF
    let VAF = computeVAF(sumOfCoeffs);

    // Нормированное количество функциональный точек
    let AFPC = FP * VAF;

    console.log("sumOfCoeffs " + sumOfCoeffs);
    console.log("normFactor " + VAF);
    console.log("before corrected " + FP);
    console.log("Corrected " + AFPC);

    state.fp.result.sumOfSystemParams = sumOfCoeffs;
    state.fp.result.isResultComputed = true;
    state.fp.result.countOfCorrectedFunctionalPoints = AFPC;
    state.fp.result.countOfFunctionalPoints = FP;
    state.fp.result.normFactor = VAF;

    return state;
}

const computeWorkAndTimeCompositional = (data) => {
    let p = computeP(data.power);
    p = 1.1;

    // Экранные формы
    let screenForms = computeScreenForms(data.compositional);
    
    // Отчёты
    let docs = computeDocs(data.compositional);

    // Модули
    let modules = data.compositional.countOfModules * 10;

    const size = screenForms + docs + modules;
    const MdpJob = (size * ((100 - data.compositional.RUSE) / 100)) / data.compositional.teamCap;

    return {
        work: +MdpJob.toFixed(2),
        time: + (3 * Math.pow(MdpJob, 0.33 + 0.2 * (p - 1.01))).toFixed(2),
        p: p,
    }

}

const computeWorkAndTimeEarlyDevelopment = (data) => {
    let p = computeP(data.power);
    
    const eArch = computeArch(data.earlyDevelopment);
    const FPper = data.FP / 100;

    let kLOC = 0;
    for (let key in data.languages) {
        kLOC += FPper * data.languages[key];
    }
    kLOC /= 1000;

    const medaJob = 2.45 * eArch * Math.pow(kLOC, p);

    return {
        work: medaJob.toFixed(2),
        time: (3.0 * Math.pow(medaJob, 0.33 + 0.2 * (p - 1.01))).toFixed(2),
        p: p,
        kLOC: kLOC,
    }
    
}

const updateCompositionalState = (compositional, {name, newValue}) => {
    if (name === 'teamCap') {
        compositional.teamCap = {...compositional.teamCap};
        compositional.teamCap.currentValue = newValue;
    } else if (name === 'RUSE') {
        compositional[name] = +newValue > 100 ? 100 : +newValue;
    } else {
        compositional[name] = +newValue;
    }

    return compositional;
}

export const Cocomo2Reducer = (state=initialState, { type, payload }) => {
    let copyState = {...state};

    switch (type) {
        case UPDATE_SYSTEM_PARAMS:
            copyState = updateSystemParamsCase(copyState, payload);

            return copyState;
        case UPDATE_CHARACTERISTICS:
            copyState = updateCharacteristicsCase(copyState, payload);

            return copyState;
        case COMPUTE_FUNCTIONAL_POINTS:
            copyState = computeFunctionalPointsCase(copyState);

            return copyState;
        case UPDATE_POWER:
            const {
                name,
                newValue,
            } = payload;

            copyState.ccm2 = {...copyState.ccm2};
            copyState.ccm2.power = {...copyState.ccm2.power};
            copyState.ccm2.power[name] = {...copyState.ccm2.power[name]};

            copyState.ccm2.power[name].currentValue = newValue;

            return copyState;
        case UPDATE_COMPOSITIONAL: {
            copyState.ccm2 = {...copyState.ccm2};
            copyState.ccm2.models = {...copyState.ccm2.models};
            copyState.ccm2.models.compositional = {...copyState.ccm2.models.compositional};

            copyState.ccm2.models.compositional = updateCompositionalState(
                copyState.ccm2.models.compositional,
                payload
            );

            return copyState;
        }
        case UPDATE_EARLY_DEVELOPMENT: {
            const {
                name,
                newValue,
            } = payload;
            copyState.ccm2 = {...copyState.ccm2};
            copyState.ccm2.models = {...copyState.ccm2.models};
            copyState.ccm2.models.earlyDevelopment = {...copyState.ccm2.models.earlyDevelopment};
            copyState.ccm2.models.earlyDevelopment[name] = {...copyState.ccm2.models.earlyDevelopment[name]};
            copyState.ccm2.models.earlyDevelopment[name].currentValue = newValue;

            return copyState;
        }
        case UPDATE_LANGUAGE: {
            const {
                name,
                newValue
            } = payload;
            copyState.ccm2 = {...copyState.ccm2};
            copyState.ccm2.languages = {...copyState.ccm2.languages};
            copyState.ccm2.languages[name] = {...copyState.ccm2.languages[name]};

            copyState.ccm2.languages[name].value = +newValue;

            return copyState;
        }
        case COMPUTE_COMPOSITIONAL: {
            const values = getValuesFromState(state);
            const result = computeWorkAndTimeCompositional(values);
            const {
                work,
                time,
                p
            } = result;

            copyState.ccm2 = {...copyState.ccm2};
            copyState.ccm2.result = {...copyState.ccm2.result};

            copyState.ccm2.result.p = p;
            copyState.ccm2.result.isPComputed = true;

            copyState.ccm2.result.compositional = {...copyState.ccm2.result.compositional};
            copyState.ccm2.result.compositional.work = +work;
            copyState.ccm2.result.compositional.time = +time;
            copyState.ccm2.result.compositional.isResultComputed = true;

            return copyState;
        }
        case COMPUTE_EARLY_DEVELOPMENT: {
            copyState.ccm2 = {...copyState.ccm2};
            copyState.ccm2.models = {...copyState.ccm2.models};
            copyState.ccm2.models.compositional = {...copyState.ccm2.models.compositional};

            const values = getValuesFromState(state);
            const result = computeWorkAndTimeEarlyDevelopment(values);

            const {
                work,
                time,
                p,
                kLOC
            } = result;

            copyState.ccm2 = {...copyState.ccm2};
            copyState.ccm2.result = {...copyState.ccm2.result};

            copyState.ccm2.result.p = p;
            copyState.ccm2.result.isPComputed = true;

            copyState.ccm2.result.earlyDevelopment = {...copyState.ccm2.result.earlyDevelopment};
            copyState.ccm2.result.earlyDevelopment.work = +work;
            copyState.ccm2.result.earlyDevelopment.time = +time;
            copyState.ccm2.result.earlyDevelopment.kLOC = +kLOC;
            copyState.ccm2.result.earlyDevelopment.isResultComputed = true;

            return copyState
        }
        default:
            return copyState;
    }
};

export const updateSystemParams = (name, value) => (dispatch) => {
    dispatch(updateSystemParamsAction({ name, value }));
};

export const updateCharacteristics = (name, { row, column }, value) => (dispatch) => {
    dispatch(updateCharacteristicsAction({
        name,
        position: { row, column },
        value
    }));
};

export const computeFunctionalPoints = () => (dispatch) => {
    dispatch(computeFunctionalPointsAction());
}

export const updatePower = (name, newValue) => (dispatch) => {
    dispatch(updatePowerAction({name, newValue}));
}

export const updateCompositional = (name, newValue) => (dispatch) => {
    dispatch(updateCompositionalAction({name, newValue}));
}

export const updateEarlyDevelopment = (name, newValue) => (dispatch) => {
    dispatch(updateEarlyDevelopmentAction({name, newValue}));
}

export const updateLanguage = (name, newValue) => (dispatch) => {
    dispatch(updateLanguageAction({name, newValue}));
}

export const computeCompositional = (name, newValue) => (dispatch) => {
    dispatch(computeCompositionalAction({name, newValue}));
}

export const computeEarlyDevelopment = () => (dispatch) => {
    dispatch(computeEarlyDevelopmentAction());
}