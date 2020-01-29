<!DOCTYPE html>
<html>
    <head>
        <title>Aggiungi gioco</title>
    </head>
    <body style="font-size: 20px;">
        <h2>Inserisci gioco</h2>
        <form id="inserisciGame" method="POST" action="/gamestore">
            {{ csrf_field() }} //controlla che il 
            <label for="title">Titolo</label> <br />
            <input name="title" id="titolo"> <br /><br />
            <label for="descrizione">Descrizione</label> <br />
            <input name="descr" id="descrizione"> <br /><br />
            <label for="prezzo">Prezzo</label> <br />
            <input name="price" id="prezzo"> <br />
            <br />
            <button type="submit">Inserisci</button>
        </form>
    </body>
</html>