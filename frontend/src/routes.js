import React from 'react';

import { Router, Route, Redirect, IndexRoute, IndexRedirect, browserHistory } from 'react-router';
import { Provider } from 'react-redux';
import { syncHistoryWithStore } from 'react-router-redux';
import { loadState } from './util/localStorage';
import configureStore from './store/configureStore';

/** ROUTES **/

// Layout
import App from './layouts/App';

// Redux
const persistedState = loadState();
const store = configureStore(persistedState);

// Create an enhanced history that syncs navigation events with the store
const history = syncHistoryWithStore(browserHistory, store);

export const getRoutes = (store) =>{

  return (
    <Route path="/" component={ App }>
      {/*<IndexRoute component={ Landing } />

      <Route path="signup" component={ Signup } />
      <Route path="login" component={ Login } />
      <Route path="verify/:token" component={ Verify } />

      <Route path="home" onEnter={ authRequired } component={ Home }>
        <IndexRoute onEnter={ goToDefaultGroup } />

        <Route path=":id">
          <IndexRoute component={ Friends } />
          <Route path="events">
            <IndexRoute component={ Events } />
            <Route path="new" component={ NewEvent } />
          </Route>
          <Route path="chat" component={ Chat } />
          <Route path="friends" component={ Friends } />
        </Route>
      </Route>*/}
    </Route>
  );
}

export default (
  <Provider store={ store }>
    <Router history={ history } >
      { getRoutes(store) }
    </Router>
  </Provider>
);