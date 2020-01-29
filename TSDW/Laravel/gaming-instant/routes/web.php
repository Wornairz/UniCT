<?php

/*
|--------------------------------------------------------------------------
| Web Routes
|--------------------------------------------------------------------------
|
| Here is where you can register web routes for your application. These
| routes are loaded by the RouteServiceProvider within a group which
| contains the "web" middleware group. Now create something great!
|
*/

Route::get('/', function () {
    return view('welcome');
});


Route::get('/games',"GamesController@index");

Route::get('/gamestore',"GamesController@create");

Route::get('/game/{game}',"GamesController@show");

Route::post('/gamestore',"GamesController@store");

Route::patch('/updategame/{game}',"GamesController@update");
