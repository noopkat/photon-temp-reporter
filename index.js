var Particle = require('particle-api-js');
var io = require('socket.io')();
var particle = new Particle();

particle.login({username: process.env.EMAIL, password: process.env.PASS})
  .then(function(data) {
    io.on('connection', function(socket) {
      // this will fetch the temperature immediately on page load
      particle.callFunction({ deviceId: process.env.DEVICE, name: 'temp', argument: '', auth: data.body.access_token })
        .then(function(data) {
          socket.emit('temperature!', { data: parseInt(data.body.return_value) });
        }, function(err) {
          console.log('An error occurred:', err);
        });

      // subscribe to stream to update temps from now on
      particle.getEventStream({ deviceId: process.env.DEVICE, name: 'temperature', auth: data.body.access_token })
        .then(function(stream) {
          stream.on('event', function(data) {
            socket.emit('temperature!', { data: parseInt(data.data) });
          });
        });
      });
    io.listen(8080);
  },
  function(err) {
    console.log('API call completed on promise fail: ', err);
  }
);
