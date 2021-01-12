const API_KEY = 'Bearer api_key'

function getSong() {
    console.log(detections);
    const emotion = detections[0].expressions.happy > detections[0].expressions.sad ? 'happy' : 'sad'; 
    axios.get(`https://api.spotify.com/v1/recommendations?market=IN&seed_genres=${emotion}`, {
        headers: {
            'Accept': 'application/json',
            'Content-Type': 'application/json',
            'Authorization': API_KEY,
        }
    })
        .then(data => {
            console.log(data);
            document.getElementById('spotify-frame').src = data.data.tracks[0].external_urls.spotify.split('/track').join('/embed/track');
            // window.open(data.data.tracks[0].external_urls.spotify);
        })
        .catch(err => console.error(err));
}