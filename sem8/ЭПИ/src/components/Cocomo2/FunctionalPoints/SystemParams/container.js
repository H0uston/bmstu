import { connect } from 'react-redux';
import { SystemParams } from './index';
import { updateSystemParams } from '../../../../store/cocomo2/reducer';

const mapStateToProps = (state) => ({
    ...state.cocomo2.fp.systemParams,
});


export const SystemParamsContainer = connect(mapStateToProps, {
    updateSystemParams,
})(SystemParams);