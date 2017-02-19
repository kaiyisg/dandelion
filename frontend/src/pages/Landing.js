import React from 'react';
import { browserHistory } from 'react-router';

import { bindActionCreators } from 'redux';
import { connect } from 'react-redux';

import RaisedButton from 'material-ui/RaisedButton';
import IconButton from 'material-ui/IconButton';

class Landing extends React.Component {

  render() {
    const { user } = this.props;

    return (
      <div id="landing-container">
          <h1>Hello</h1>
      </div>
    );
  }
}

const mapDispatchToProps = (dispatch) => {
  return {
    
  };
};

const mapStateToProps = (state) => {
  return {
    user: state.user.userObject
  };
};

export default connect(mapStateToProps, mapDispatchToProps)(Landing);