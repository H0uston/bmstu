import { connect } from 'react-redux';
import { computeFunctionalPoints } from '../../store/cocomo2/reducer';

const mapStateToProps = (state) => ({ })


export const Cocomo2Container = connect(mapStateToProps, {
    computeFunctionalPoints,
});