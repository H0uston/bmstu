import {
    applyMiddleware,
    combineReducers,
    compose,
    createStore
} from 'redux';
import thunkMiddleware from 'redux-thunk';
import { Cocomo1Reducer } from './cocomo1/reducer';
import { Cocomo2Reducer } from './cocomo2/reducer';

let reducers = combineReducers({
    cocomo1: Cocomo1Reducer,
    cocomo2: Cocomo2Reducer,
});

const composeEnhancers = window.__REDUX_DEVTOOLS_EXTENSION_COMPOSE__ || compose;
let store = createStore(reducers, composeEnhancers(applyMiddleware(thunkMiddleware)));

export default store;

