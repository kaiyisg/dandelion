export function callGeoEnhaceAddress(){
				var GE = new GEOAPIS_V1.geoEnhance('x7x8xAPAumgfBownML8XKB2LDaqiALry');
				//enter the returned access token as explained in Obtaining Credentials section
				GE.getAddress({latitude:42.5309, longitude:-73.6572, searchRadius:20}, 'geoApisCallback');
				
			}			
export function geoApisCallback(data){
				if(data !== undefined){
					$('#ResponseDiv').html(JSON.stringify(data));
				}
			}

export function get(url) {
  // Return a new promise.
  return new Promise(function(resolve, reject) {
    // Do the usual XHR stuff
    var req = new XMLHttpRequest();
    req.open('GET', url);

    req.onload = function() {
      // This is called even on 404 etc
      // so check the status
      if (req.status == 200) {
        // Resolve the promise with the response text
        resolve(req.response);
      }
      else {
        // Otherwise reject with the status text
        // which will hopefully be a meaningful error
        reject(Error(req.statusText));
      }
    };

    // Handle network errors
    req.onerror = function() {
      reject(Error("Network Error"));
    };

    // Make the request
    req.send();
  });
}