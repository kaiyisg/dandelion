import React, { Component } from 'react';
import MuiTheme from './MuiTheme';
import MuiThemeProvider from 'material-ui/styles/MuiThemeProvider';
import logo from './logo.svg';
import './App.css';

import { makeRouteSlug } from '../util/helper';

class App extends Component {

  static propTypes = {
    children: React.PropTypes.element.isRequired,
    routes: React.PropTypes.array.isRequired,
    location: React.PropTypes.object,
    actions: React.PropTypes.object.isRequired,
  };

  render() {
    return (
      <MuiThemeProvider muiTheme={ MuiTheme }>
        <div>
          <div id="root-container">
            <div id="main" className={`page-${ makeRouteSlug(this.props.routes) }`}>
              { this.props.children }
            </div>
          </div>
        </div>
      </MuiThemeProvider>
    );
  }
}

export default App;
