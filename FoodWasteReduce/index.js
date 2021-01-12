function createCard(data) {
    let ings = [];
    data.usedIngredients.forEach(ing => {
        ings.push(`<li>${ing.name} ${ing.unit}</li>`);
    });

    data.missedIngredients.forEach(ing => {
        ings.push(`<li>${ing.name} ${ing.unit}</li>`);
    });

    ings = ings.join('\n');

    return `
    <div class="card">

                    <div class="image">
                        <img src="${data.image}"
                            width="100%">
                    </div>

                    <div class="text">

                        <h3>${data.title}</h3>
                        <p>Ingredients used: <ol>${ings}</ol></p>

                    </div>

                </div>
    `
}

function makeReq(ing) {
    axios.get(`https://api.spoonacular.com/recipes/findByIngredients?ingredients=${ing}&number=2&apiKey=2dce97f7bd1d48978c10fa5869c02d61`)
        .then(res => {
            console.log(res);
            res.data.forEach((rec) => {
                $('#cards').append(createCard(rec));
            })
        })
}

function search() {
    let inputVal = document.querySelector('#search').value.trim();
    if (!inputVal) alert('Come on, empty search?')
    inputVal = inputVal.split(',');
    inputVal.forEach((element, index) => {
        inputVal[index] = element.trim();
    });
    inputVal = inputVal.join(',');
    inputVal = encodeURIComponent(inputVal);

    makeReq(inputVal);
}