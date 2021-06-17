import {computeCompositional, updateCompositional} from "../../../../store/cocomo2/reducer";
import {connect} from "react-redux";
import {Compositional} from "./index";

const mapStateToProps = (state) => ({
    RUSE: state.cocomo2.ccm2.models.compositional.RUSE,
    teamCap: state.cocomo2.ccm2.models.compositional.teamCap,
    simpleForms: state.cocomo2.ccm2.models.compositional.simpleForms,
    middleForms: state.cocomo2.ccm2.models.compositional.middleForms,
    difficultForms: state.cocomo2.ccm2.models.compositional.difficultForms,
    simpleReports: state.cocomo2.ccm2.models.compositional.simpleReports,
    middleReports: state.cocomo2.ccm2.models.compositional.middleReports,
    difficultReports: state.cocomo2.ccm2.models.compositional.difficultReports,
    countOfModules: state.cocomo2.ccm2.models.compositional.countOfModules,

    result: state.cocomo2.ccm2.result,
});

export const CompositionalContainer = connect(mapStateToProps, {
    updateCompositional,
    computeCompositional,
})(Compositional);