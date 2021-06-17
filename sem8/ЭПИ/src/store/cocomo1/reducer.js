import {
    ACAP,
    AEXP,
    CPLX,
    DATA,
    LANGUAGES,
    LEXP,
    mode,
    MODP,
    PCAP,
    RELY,
    SCED,
    STOR,
    TIME,
    TOOL,
    TURN,
    VEXP,
    VIRT,
} from './constants';
import {
    UPDATE_ACAP,
    UPDATE_AEXP,
    UPDATE_CPLX,
    UPDATE_DATA,
    UPDATE_KLOC,
    UPDATE_LANGUAGE,
    UPDATE_LEXP, UPDATE_MAN, UPDATE_MMNG, UPDATE_MMNL,
    UPDATE_MODE,
    UPDATE_MODP,
    UPDATE_MOFF,
    UPDATE_MPROG,
    UPDATE_MPROJ,
    UPDATE_MTEST,
    UPDATE_MVER,
    UPDATE_PCAP,
    UPDATE_RELY,
    UPDATE_RESULT,
    UPDATE_SCED,
    UPDATE_STOR,
    UPDATE_TAN, UPDATE_TDP, UPDATE_TIAT,
    UPDATE_TIME, UPDATE_TKATOM,
    UPDATE_TMNG,
    UPDATE_TMNL,
    UPDATE_TOFF,
    UPDATE_TOOL, UPDATE_TPADT, UPDATE_TPP,
    UPDATE_TPROG,
    UPDATE_TPROJ,
    UPDATE_TTEST,
    UPDATE_TURN,
    UPDATE_TVER,
    UPDATE_VEXP,
    UPDATE_VIRT, UPDATE_WDP, UPDATE_WIAT, UPDATE_WKATOM, UPDATE_WPADT, UPDATE_WPP,
    updateAcap,
    updateAexp,
    updateCplx,
    updateData,
    updateKloc,
    updateLanguage,
    updateLexp, updateMAN, updateMMNG, updateMMNL,
    updateMode,
    updateModp, updateMOFF, updateMPROG, updateMPROJ, updateMTEST, updateMVER,
    updatePcap,
    updateRely,
    updateResult,
    updateSced,
    updateStor,
    updateTAN, updateTDP, updateTIAT,
    updateTime, updateTKATOM,
    updateTMNG,
    updateTMNL,
    updateTOFF,
    updateTool, updateTPADT, updateTPP,
    updateTPROG,
    updateTPROJ,
    updateTTEST,
    updateTurn,
    updateTVER,
    updateVexp,
    updateVirt, updateWDP, updateWIAT, updateWKATOM, updateWPADT, updateWPP
} from './actions';
import {
    computeCocomo1,
    getValuesFromState
} from './helpers';

const initialState = {
    KLOC: 100,
    LANGUAGES,
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
    mode,
    tAn: 4,
    tProj: 12,
    tProg: 44,
    tTest: 6,
    tVer: 14,
    tOff: 7,
    tMng: 7,
    tMnl: 6,
    mAn: 39,
    mProj: 117,
    mProg: 428,
    mTest: 58,
    mVer: 136,
    mOff: 68,
    mMng: 68,
    mMnl: 58,
    wpadt: 0,
    tpadt: 0,
    wpp: 18,
    tpp: 36,
    wdp: 25,
    tdp: 18,
    wkatom: 26,
    tkatom: 18,
    tiat: 28,
    wiat: 31,

    isResultComputed: false,
    result: null,
}

export const Cocomo1Reducer = (state=initialState, { type, payload}) => {
    const copyState = { ...state };

    switch(type) {
        case UPDATE_KLOC: {
            copyState.KLOC = payload;

            return copyState;
        }
        case UPDATE_LANGUAGE: {
            copyState.LANGUAGES = {...copyState.LANGUAGES};
            copyState.LANGUAGES.currentValue = payload;

            return copyState;
        }
        case UPDATE_RELY: {
            copyState.RELY = {...copyState.RELY};
            copyState.RELY.currentValue = payload;

            return copyState;
        }
        case UPDATE_DATA: {
            copyState.DATA = {...copyState.DATA};
            copyState.DATA.currentValue = payload;

            return copyState;
        }
        case UPDATE_TIME: {
            copyState.TIME = {...copyState.TIME};
            copyState.TIME.currentValue = payload;

            return copyState;
        }
        case UPDATE_STOR: {
            copyState.STOR = {...copyState.STOR};
            copyState.STOR.currentValue = payload;

            return copyState;
        }
        case UPDATE_CPLX: {
            copyState.CPLX = {...copyState.CPLX};
            copyState.CPLX.currentValue = payload;

            return copyState;
        }
        case UPDATE_VIRT: {
            copyState.VIRT = {...copyState.VIRT};
            copyState.VIRT.currentValue = payload;

            return copyState;
        }
        case UPDATE_TURN: {
            copyState.TURN = {...copyState.TURN};
            copyState.TURN.currentValue = payload;

            return copyState;
        }
        case UPDATE_ACAP: {
            copyState.ACAP = {...copyState.ACAP};
            copyState.ACAP.currentValue = payload;

            return copyState;
        }
        case UPDATE_AEXP: {
            copyState.AEXP = {...copyState.AEXP};
            copyState.AEXP.currentValue = payload;

            return copyState;
        }
        case UPDATE_PCAP: {
            copyState.PCAP = {...copyState.PCAP};
            copyState.PCAP.currentValue = payload;

            return copyState;
        }
        case UPDATE_VEXP: {
            copyState.VEXP = {...copyState.VEXP};
            copyState.VEXP.currentValue = payload;

            return copyState;
        }
        case UPDATE_LEXP: {
            copyState.LEXP = {...copyState.LEXP};
            copyState.LEXP.currentValue = payload;

            return copyState;
        }
        case UPDATE_MODP: {
            copyState.MODP = {...copyState.MODP};
            copyState.MODP.currentValue = payload;

            return copyState;
        }
        case UPDATE_TOOL: {
            copyState.TOOL = {...copyState.TOOL};
            copyState.TOOL.currentValue = payload;

            return copyState;
        }
        case UPDATE_SCED: {
            copyState.SCED = {...copyState.SCED};
            copyState.SCED.currentValue = payload;

            return copyState;
        }
        case UPDATE_MODE: {
            copyState.mode = {...copyState.mode};
            copyState.mode.currentValue = payload;

            return copyState;
        }
        case UPDATE_TAN: {
            copyState.tAn = payload;

            return copyState;
        }
        case UPDATE_TPROG: {
            copyState.tProg = payload;

            return copyState;
        }
        case UPDATE_TPROJ: {
            copyState.tProj = payload;

            return copyState;
        }
        case UPDATE_TTEST: {
            copyState.tTest = payload;

            return copyState;
        }
        case UPDATE_TVER: {
            copyState.tVer = payload;

            return copyState;
        }
        case UPDATE_TOFF: {
            copyState.tOff = payload;

            return copyState;
        }
        case UPDATE_TMNG: {
            copyState.tMng = payload;

            return copyState;
        }
        case UPDATE_TMNL: {
            copyState.tMnl = payload;

            return copyState;
        }
        case UPDATE_MAN: {
            copyState.mAn = payload;

            return copyState;
        }
        case UPDATE_MPROG: {
            copyState.mProg = payload;

            return copyState;
        }
        case UPDATE_MPROJ: {
            copyState.mProj = payload;

            return copyState;
        }
        case UPDATE_MTEST: {
            copyState.mTest = payload;

            return copyState;
        }
        case UPDATE_MVER: {
            copyState.mVer = payload;

            return copyState;
        }
        case UPDATE_MOFF: {
            copyState.mOff = payload;

            return copyState;
        }
        case UPDATE_MMNG: {
            copyState.mMng = payload;

            return copyState;
        }
        case UPDATE_MMNL: {
            copyState.mMnl = payload;

            return copyState;
        }
        case UPDATE_WPADT: {
            copyState.wpadt = payload;

            return copyState;
        }
        case UPDATE_TPADT: {
            copyState.tpadt = payload;

            return copyState;
        }
        case UPDATE_WPP: {
            copyState.wpp = payload;

            return copyState;
        }
        case UPDATE_TPP: {
            copyState.tpp = payload;

            return copyState;
        }
        case UPDATE_WDP: {
            copyState.wdp = payload;

            return copyState;
        }
        case UPDATE_TDP: {
            copyState.tdp = payload;

            return copyState;
        }
        case UPDATE_WKATOM: {
            copyState.wkatom = payload;

            return copyState;
        }
        case UPDATE_TKATOM: {
            copyState.tkatom = payload;

            return copyState;
        }
        case UPDATE_TIAT: {
            copyState.tiat = payload;

            return copyState;
        }
        case UPDATE_WIAT: {
            copyState.wiat = payload;

            return copyState;
        }
        case UPDATE_RESULT: {
            const values = getValuesFromState(state);
            copyState.result = computeCocomo1(values);
            copyState.isResultComputed = true;

            return copyState;
        }
        default: {
            return copyState;
        }
    }
}

export const setKloc = (count) => (dispatch) => {
    dispatch(updateKloc(count));
};

export const setLanguage = (option) => (dispatch) => {
    dispatch(updateLanguage(option));
};

export const setRely = (option) => (dispatch) => {
    dispatch(updateRely(option));
};

export const setCplx = (option) => (dispatch) => {
    dispatch(updateCplx(option));
};

export const setData = (option) => (dispatch) => {
    dispatch(updateData(option));
};

export const setTime = (option) => (dispatch) => {
    dispatch(updateTime(option));
};

export const setStor = (option) => (dispatch) => {
    dispatch(updateStor(option));
};

export const setVirt = (option) => (dispatch) => {
    dispatch(updateVirt(option));
};

export const setTurn = (option) => (dispatch) => {
    dispatch(updateTurn(option));
};

export const setAcap = (option) => (dispatch) => {
    dispatch(updateAcap(option));
};

export const setAexp = (option) => (dispatch) => {
    dispatch(updateAexp(option));
};

export const setPcap = (option) => (dispatch) => {
    dispatch(updatePcap(option));
};

export const setVexp = (option) => (dispatch) => {
    dispatch(updateVexp(option));
};

export const setLexp = (option) => (dispatch) => {
    dispatch(updateLexp(option));
};

export const setModp = (option) => (dispatch) => {
    dispatch(updateModp(option));
};

export const setTool = (option) => (dispatch) => {
    dispatch(updateTool(option));
};

export const setSced = (option) => (dispatch) => {
    dispatch(updateSced(option));
};

export const setMode = (option) => (dispatch) => {
    dispatch(updateMode(option));
};

export const computeResult = () => (dispatch) => {
    dispatch(updateResult());
}

export const setTAN = (count) => (dispatch) => {
    dispatch(updateTAN(count));
}

export const setTPROJ = (count) => (dispatch) => {
    dispatch(updateTPROJ(count));
};

export const setTPROG = (count) => (dispatch) => {
    dispatch(updateTPROG(count));
};

export const setTTEST = (count) => (dispatch) => {
    dispatch(updateTTEST(count));
};

export const setTVER = (count) => (dispatch) => {
    dispatch(updateTVER(count));
};

export const setTOFF = (count) => (dispatch) => {
    dispatch(updateTOFF(count));
};

export const setTMNG = (count) => (dispatch) => {
    dispatch(updateTMNG(count));
};

export const setTMNL = (count) => (dispatch) => {
    dispatch(updateTMNL(count));
};

export const setMAN = (count) => (dispatch) => {
    dispatch(updateMAN(count));
}

export const setMPROJ = (count) => (dispatch) => {
    dispatch(updateMPROJ(count));
};

export const setMPROG = (count) => (dispatch) => {
    dispatch(updateMPROG(count));
};

export const setMTEST = (count) => (dispatch) => {
    dispatch(updateMTEST(count));
};

export const setMVER = (count) => (dispatch) => {
    dispatch(updateMVER(count));
};

export const setMOFF = (count) => (dispatch) => {
    dispatch(updateMOFF(count));
};

export const setMMNG = (count) => (dispatch) => {
    dispatch(updateMMNG(count));
};

export const setMMNL = (count) => (dispatch) => {
    dispatch(updateMMNL(count));
};

export const setWPADT = (count) => (dispatch) => {
    dispatch(updateWPADT(count));
};

export const setTPADT = (count) => (dispatch) => {
    dispatch(updateTPADT(count));
};

export const setWPP = (count) => (dispatch) => {
    dispatch(updateWPP(count));
};

export const setTPP = (count) => (dispatch) => {
    dispatch(updateTPP(count));
};

export const setWDP = (count) => (dispatch) => {
    dispatch(updateWDP(count));
};

export const setTDP = (count) => (dispatch) => {
    dispatch(updateTDP(count));
};

export const setWKATOM = (count) => (dispatch) => {
    dispatch(updateWKATOM(count));
};

export const setTKATOM = (count) => (dispatch) => {
    dispatch(updateTKATOM(count));
};

export const setTIAT = (count) => (dispatch) => {
    dispatch(updateTIAT(count));
};

export const setWIAT = (count) => (dispatch) => {
    dispatch(updateWIAT(count));
};