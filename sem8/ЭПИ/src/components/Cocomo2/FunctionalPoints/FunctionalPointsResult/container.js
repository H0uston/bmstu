import { connect } from 'react-redux';
import { FunctionalPointsResult } from './index';

const mapStateToProps = (state) => ({
    sumOfSystemParams: state.cocomo2.fp.result.sumOfSystemParams,
    countOfFunctionalPoints: state.cocomo2.fp.result.countOfFunctionalPoints,
    countOfCorrectedFunctionalPoints: state.cocomo2.fp.result.countOfCorrectedFunctionalPoints,
    normFactor: state.cocomo2.fp.result.normFactor,
})

export const FunctionalPointsResultContainer = connect(mapStateToProps, {})(FunctionalPointsResult);