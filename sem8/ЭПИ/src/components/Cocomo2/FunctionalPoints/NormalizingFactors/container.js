import { NormalizingFactors } from './index';
import { connect } from 'react-redux';
import { updateCharacteristics } from '../../../../store/cocomo2/reducer';

const mapStateToProps = (state) => ({
    ...state.cocomo2.fp.characteristics,
});


export const NormalizingFactorsContainer = connect(mapStateToProps, {
    updateCharacteristics,
})(NormalizingFactors);