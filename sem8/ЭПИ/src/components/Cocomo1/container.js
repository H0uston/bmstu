import { connect } from 'react-redux';
import { Cocomo1 } from './index';
import {
    computeResult,
    setAcap,
    setAexp,
    setCplx,
    setData,
    setKloc,
    setLanguage,
    setLexp, setMAN, setMMNG, setMMNL,
    setMode,
    setModp, setMOFF, setMPROG, setMPROJ, setMTEST, setMVER,
    setPcap,
    setRely,
    setSced,
    setStor,
    setTAN, setTDP, setTIAT,
    setTime, setTKATOM,
    setTMNG,
    setTMNL,
    setTOFF,
    setTool, setTPADT, setTPP,
    setTPROG,
    setTPROJ,
    setTTEST,
    setTurn,
    setTVER,
    setVexp,
    setVirt, setWDP, setWIAT, setWKATOM, setWPADT, setWPP
} from '../../store/cocomo1/reducer';


const mapStateToProps = (state) => ({
    kloc: state.cocomo1.KLOC,
    languages: state.cocomo1.LANGUAGES,
    rely: state.cocomo1.RELY,
    data: state.cocomo1.DATA,
    cplx: state.cocomo1.CPLX,
    time: state.cocomo1.TIME,
    stor: state.cocomo1.STOR,
    virt: state.cocomo1.VIRT,
    turn: state.cocomo1.TURN,
    acap: state.cocomo1.ACAP,
    aexp: state.cocomo1.AEXP,
    pcap: state.cocomo1.PCAP,
    vexp: state.cocomo1.VEXP,
    lexp: state.cocomo1.LEXP,
    modp: state.cocomo1.MODP,
    tool: state.cocomo1.TOOL,
    sced: state.cocomo1.SCED,
    mode: state.cocomo1.mode,
    tAn: state.cocomo1.tAn,
    tProj: state.cocomo1.tProj,
    tProg: state.cocomo1.tProg,
    tTest: state.cocomo1.tTest,
    tVer: state.cocomo1.tVer,
    tOff: state.cocomo1.tOff,
    tMng: state.cocomo1.tMng,
    tMnl: state.cocomo1.tMnl,
    mAn: state.cocomo1.mAn,
    mProj: state.cocomo1.mProj,
    mProg: state.cocomo1.mProg,
    mTest: state.cocomo1.mTest,
    mVer: state.cocomo1.mVer,
    mOff: state.cocomo1.mOff,
    mMng: state.cocomo1.mMng,
    mMnl: state.cocomo1.mMnl,
    wpadt: state.cocomo1.wpadt,
    tpadt: state.cocomo1.tpadt,
    wpp: state.cocomo1.wpp,
    tpp: state.cocomo1.tpp,
    wdp: state.cocomo1.wdp,
    tdp: state.cocomo1.tdp,
    wkatom: state.cocomo1.wkatom,
    tkatom: state.cocomo1.tkatom,
    tiat: state.cocomo1.tiat,
    wiat: state.cocomo1.wiat,
    isResultComputed: state.cocomo1.isResultComputed,
    result: state.cocomo1.result,
});

export default connect(mapStateToProps, {
    setKloc,
    setLanguage,
    setRely,
    setData,
    setCplx,
    setTime,
    setStor,
    setVirt,
    setTurn,
    setAcap,
    setAexp,
    setPcap,
    setVexp,
    setLexp,
    setModp,
    setTool,
    setSced,
    setMode,
    setTAN,
    setTPROJ,
    setTPROG,
    setTTEST,
    setTVER,
    setTOFF,
    setTMNG,
    setTMNL,
    setMAN,
    setMPROJ,
    setMPROG,
    setMTEST,
    setMVER,
    setMOFF,
    setMMNG,
    setMMNL,
    computeResult,
    setWPADT,
    setTPADT,
    setWPP,
    setTPP,
    setWDP,
    setTDP,
    setWKATOM,
    setTKATOM,
    setTIAT,
    setWIAT,
})(Cocomo1)

