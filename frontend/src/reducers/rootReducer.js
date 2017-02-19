import { combineReducers } from 'redux';
import { routerReducer } from 'react-router-redux';

// Reducers

// Refactor the rest soon

const rootReducer = combineReducers({

  // Add routerReducer
  routing: routerReducer,
});

export default rootReducer;