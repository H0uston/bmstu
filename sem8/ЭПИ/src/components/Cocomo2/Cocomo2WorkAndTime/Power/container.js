import {updatePower} from "../../../../store/cocomo2/reducer";
import {connect} from "react-redux";
import {Power} from "./index";

const mapStateToProps = (state) => ({
    PREC: state.cocomo2.ccm2.power.PREC,
    FLEX: state.cocomo2.ccm2.power.FLEX,
    RESL: state.cocomo2.ccm2.power.RESL,
    TEAM: state.cocomo2.ccm2.power.TEAM,
    PMAT: state.cocomo2.ccm2.power.PMAT,
});

export const PowerContainer = connect(mapStateToProps, {
    updatePower,
})(Power);