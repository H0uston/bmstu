import { connect } from 'react-redux';
import { computeFunctionalPoints } from '../../../store/cocomo2/reducer';
import { FunctionalPoints } from './index';

const mapStateToProps = (state) => ({
    isResultComputed: state.cocomo2.fp.result.isResultComputed,
});

export const FunctionalPointsContainer = connect(mapStateToProps, {
    computeFunctionalPoints,
})(FunctionalPoints);