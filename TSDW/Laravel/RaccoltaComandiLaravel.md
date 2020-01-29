
Raccolta comandi per l'uso di Laravel
-------------------------------------

### Passi per la creazione di una tabella e relativo modello
```
laravel new gaming-instant    
cd gaming-instant/  
code gaming-instant/  
systemctl start mariadb.service  
mysql -u root  
cd gaming-instant/  
php artisan make:model Game  
php artisan make:migration create_games_table  
php artisan migrate:status  
php artisan migrate  
php artisan migrate:status  
mysql -u root  
```

#### Osservazioni
*   string = varchar(255)
*   text = testo illimitato
*   game (model) si va a cercare una tabella games (tabella nel database)
*   Per aggiornare le tabelle dalla igrazione devo prima fare un rollback (migrate:rollback)
*   e poi fare nuovamente migrate
*   Abbiamo modificato la tabella inserendo il prezzo nullable

### Comandi per sincronizzare le modifiche dal model al database
```
php artisan migrate:status  
php artisan migrate:rollback  
php artisan migrate  
```

#### Osservazioni
*   Per sincronizzare le modifice va fatto un rollback e successivamente una nuova migrazione

### Creazione di un controller
```
php artisan make:controller GamesController -r
```

#### Osservazioni

### Uso del tinker per aggiungere un elemento
```
php artisan tinker  
  
$game1=new App\Game();  
=> App\Game {#3017}  
>>> $game1->name='Sekiro';  
=> "Sekiro"  
>>> $game1->description='GOTY2019';  
=> "GOTY2019"  
>>> $game1->price=50;  
=> 50  
>>> $game1->save();  
=> true
```
#### Osservazioni

### Lista delle rotte definite
```
php artisan route::list
```

### Osservazioni
*   Mostra la lista delle rotte definite in web.php