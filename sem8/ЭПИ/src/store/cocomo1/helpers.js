import {
    BUILDIN_MODE,
    INTER_MODE,
    SIMPLE_MODE
} from './constants';

export const getValuesFromState = (state) => {
    const result = {};
    for (let key in state) {
        if (typeof state[key] === 'object' && state[key] !== null && key !== 'result') {
            const currentValue = state[key].currentValue;
            result[key] = state[key].options[currentValue];
        } else if (typeof state[key] !== 'boolean' && key !== 'result') {
            result[key] = state[key];
        }
    }

    console.log("Params: ", result);

    return result;
}

const computeEaf = (values) => {
    const {
        RELY,
        DATA,
        CPLX,
        TIME,
        STOR,
        VIRT,
        TURN,
        ACAP,
        AEXP,
        PCAP,
        VEXP,
        LEXP,
        MODP,
        TOOL,
        SCED,
    } = values;

    return RELY * DATA * CPLX * TIME * STOR * VIRT * TURN * ACAP * AEXP * PCAP * VEXP * LEXP * MODP * TOOL * SCED;
}

const computeManAndTimeMonth = (values) => {
    const eaf = computeEaf(values);

    const { KLOC, LANGUAGES } = values;

    const klocAndLang = KLOC / LANGUAGES;

    switch (values.mode) {
        case (SIMPLE_MODE): {
            const manMonth = 3.2 * eaf * Math.pow(klocAndLang, 1.05); // TODO разобраться
            const timeMonth = 2.5 * Math.pow(manMonth, 0.38);

            return { manMonth, timeMonth };
        }
        case (INTER_MODE): {
            const manMonth = 3 * eaf * Math.pow(klocAndLang, 1.12); // TODO разобраться
            const timeMonth = 2.5 * Math.pow(manMonth, 0.35);

            return { manMonth, timeMonth };
        }
        case (BUILDIN_MODE): {
            const manMonth = 2.8 * eaf * Math.pow(klocAndLang, 1.2); // TODO разобраться
            const timeMonth = 2.5 * Math.pow(manMonth, 0.32);

            return { manMonth, timeMonth };
        }
        default: {
            throw Error();
        }
    }
}

export const computeBudget = (manMonth, values) => {
    const {
        tAn,
        tProj,
        tProg,
        tTest,
        tVer,
        tOff,
        tMng,
        tMnl,
    } = values;

    return {
        mAn: (tAn / 100) * manMonth,
        mProj: (tProj / 100) * manMonth,
        mProg: (tProg / 100) * manMonth,
        mTest: (tTest / 100) * manMonth,
        mVer: (tVer / 100) * manMonth,
        mOff: (tOff / 100) * manMonth,
        mMng: (tMng / 100) * manMonth,
        mMnl: (tMnl / 100) * manMonth,
    };
};

const computeWork = (manMonth, values) => {
    const {
        wpadt,
        wpp,
        wdp,
        wkatom,
        wiat
    } = values;

    return {
        padt: ((wpadt || 8) / 100) * manMonth,
        pp: (wpp / 100) * manMonth,
        dp: (wdp / 100) * manMonth,
        katom: (wkatom / 100) * manMonth,
        iat: (wiat / 100) * manMonth,
    }
}

const computeTime = (timeMonth, values) => {
    const {
        tpadt,
        tpp,
        tdp,
        tkatom,
        tiat
    } = values;

    return {
        padt: ((tpadt || 36) / 100) * timeMonth,
        pp: (tpp / 100) * timeMonth,
        dp: (tdp / 100) * timeMonth,
        katom: (tkatom / 100) * timeMonth,
        iat: (tiat / 100) * timeMonth,
    }
}

const computeDataWT = (work, time) => {
    const dataWt = {};
    for (let key in work) {
        dataWt[key] = work[key] / time[key];
    }

    return dataWt;
}

export const computeCocomo1 = (values) => {
    const { manMonth, timeMonth } = computeManAndTimeMonth(values);
    console.log('manMonth: ', manMonth);
    console.log('timeMonth: ', timeMonth);
    const budget = computeBudget(manMonth, values);
    console.log('budget: ', budget);
    const work = computeWork(manMonth, values);
    console.log('work: ', work);
    const time = computeTime(timeMonth, values);
    console.log('time: ', time);
    const dataWt = computeDataWT(work, time);
    console.log('dataWT: ', dataWt);

    return {
        manMonth,
        timeMonth,
        budget,
        work,
        time,
        dataWt,
    }
}
