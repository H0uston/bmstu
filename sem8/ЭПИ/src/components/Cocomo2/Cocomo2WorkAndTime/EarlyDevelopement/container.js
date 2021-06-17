import {
    computeEarlyDevelopment,
    updateEarlyDevelopment,
    updateLanguage
} from "../../../../store/cocomo2/reducer";
import {connect} from "react-redux";
import {EarlyDevelopment} from "./index";

const mapStateToProps = (state) => ({
    ...state.cocomo2.ccm2.models.earlyDevelopment,
    languages: { ...state.cocomo2.ccm2.languages },
    result: state.cocomo2.ccm2.result,
});

export const EarlyDevelopmentContainer = connect(mapStateToProps, {
    updateEarlyDevelopment,
    updateLanguage,
    computeEarlyDevelopment,
})(EarlyDevelopment);