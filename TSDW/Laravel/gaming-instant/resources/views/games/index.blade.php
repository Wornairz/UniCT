@extends('layout')
@section('title',"Games Index")

@section('content')
<h1> Lista giochi</h1>
    <ul>
    @foreach ($GAMES as $game)
        <li>{{$game->name }} {{$game->description}} {{ $game->price}}</li><br>
    @endforeach
    </ul>
@endsection