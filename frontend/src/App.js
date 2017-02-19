import React, { Component } from 'react';
import MuiTheme from './MuiTheme';
import MuiThemeProvider from 'material-ui/styles/MuiThemeProvider';
import logo from './logo.svg';
import './App.css';

import { makeRouteSlug } from './util/helper';

class App extends Component {

  static propTypes = {
    children: React.PropTypes.element.isRequired,
    routes: React.PropTypes.array.isRequired,
    location: React.PropTypes.object,
    actions: React.PropTypes.object.isRequired,
  };

  render() {
    return (
      <div className="App">
        <div className="App-header">
          <img src={logo} className="App-logo" alt="logo" />
          <h2>Welcome to React</h2>
        </div>
        <p className="App-intro">
          To get started, edit <code>src/App.js</code> and save to reload.
        </p>
      </div>
    );
  }
}

export default App;
