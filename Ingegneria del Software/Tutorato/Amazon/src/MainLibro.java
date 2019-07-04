import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;
import java.util.stream.IntStream;
import java.util.stream.Stream;

public class MainLibro {

	public static void main(String[] args) {
		//query0(); // Stampare 10 libri (usando generate)
		//query1(); // Contare tutti i libri CYBERPUNK
		//query2(); // Lista dei titoli dei libri CYBERPUNK o FANTASY 
		//query3(); // Somma dei costi di tutti i libri
		//query4(); // Somma in dollari dei costi di tutti i libri (1 EUR = 1.12 USD)
		//query5(); // Stampa tutti i libri con prezzo compreso tra 10€ e 15€
		//query6(); // Titolo del Libro meno caro (ma a partire da 12€)
		//query7(); // Stampa la lista dei libri ordinati per prezzo
		
		//query8(); // Stampa il conteggio vendite per ogni libro (senza groupingBy)
		//query9(); // Stampa i libri raggruppati per categoria (senza groupingBy)
		
		//query10(); // Creare una lista di libri fantasy da "Harry Potter 1" a "Harry Potter 7", tutti da 15 euro 
		//query11(); // Sfruttando il metodo precedente, ottenere la lista di libri e mescolarla in ordine casuale
		//query12(); // Data una lista di libri, stampare il primo che ha un prezzo maggiore del precedente (Funzione Pura)
		//query13(); // Data una lista di libri, stampare il primo che ha un prezzo maggiore del precedente (Funzione Non Pura)
		//query14(); // Data una lista di libri, applicare ad ogni libro uno sconto che dipende dalla categoria
				   // -	FANTASY -5%
				   // -	CYBERPUNK -10%
				   // -	THRILLER -50%
		           // -	STORICO -0%
		           // -	INFORMATICA x2+10% (niente sconti per noi programmatori...)
	}
	
	public static void query0() {
		Stream.generate(Libro::gen).limit(10).forEach(System.out::println);
	}
	
	public static void query1() { //Contare libri CYBERPUNK
		System.out.println("---------------");
		System.out.println("#Query 1");
		long cnt = Stream.generate(Libro::gen).limit(10).filter(x -> x.getCategoria().equals(Libro.Categoria.CYBERPUNK)).count();
		System.out.println("I libri CYBERPUNK SONO " + cnt);
	}
	
	public static List<String> query2() { //Lista dei titoli libri CYBERPUNK o FANTASY
		System.out.println("---------------");
		System.out.println("#Query 2");
		List<String> listaLibri = Stream.generate(Libro::gen)
				.limit(10)
				.filter(x -> x.getCategoria().equals(Libro.Categoria.CYBERPUNK) || x.getCategoria().equals(Libro.Categoria.FANTASY))
				.map(x -> x.getTitolo())
				.collect(Collectors.toList());
		System.out.println(listaLibri);
		return listaLibri;
	}

	public static void query3() { //Somma dei costi di tutti i libri
		System.out.println("---------------");
		System.out.println("#Query 3");
		/*Optional<Integer> sum = Stream.generate(Libro::gen)
						.limit(10)
						.map(x -> x.getPrezzo())
						.reduce(Integer::sum);
		
		if(sum.isPresent()) {
			System.out.println("La somma è " + sum.get());
		}*/
		int sum = Stream.generate(Libro::gen)
								.limit(10)
								.mapToInt(x -> x.getPrezzo())
								.sum();
		System.out.println("La somma è " + sum);
	}
	
	public static void query4() { //Somma in dollari dei costi di tutti i libri
		System.out.println("---------------");
		System.out.println("#Query 4");
		Optional<Long> sum = Stream.generate(Libro::gen)
						.limit(10)
						.map(x -> x.getPrezzo()*1.12)
						.map(Math::round)
						.reduce(Long::sum);
		if(sum.isPresent()) {
			System.out.println("La somma è " + sum.get());
		}
	}
	
	public static void query5() { //Stampare tutti i libri con costo da 10€ e 15€
		System.out.println("---------------");
		System.out.println("#Query 5");
		Stream.generate(Libro::gen)
						.limit(10)
						.filter(x -> x.getPrezzo()>=10 && x.getPrezzo()<=15)
						//.filter(x -> x.getPrezzo()>=10)
						//.filter(x -> x.getPrezzo()<=15)
						.forEach(System.out::println);
	}
	
	public static void query6() { //Titolo del libro meno caro a partire da 12€
		System.out.println("---------------");
		System.out.println("#Query 6");
		Optional<Libro> l = Stream.generate(Libro::gen)
						.limit(10)
						.filter(x -> x.getPrezzo()>=12)
						.min(Comparator.comparing(Libro::getPrezzo));
		if(l.isPresent()) {
			System.out.println("Il titolo è " + l.get().getTitolo());
		}
		else {
			System.out.println("Nessun libro trovato");
		}
	}
	
	public static void query7() { // Stampa la lista dei libri ordinati per prezzo
		System.out.println("---------------");
		System.out.println("#Query 7");
		Stream.generate(Libro::gen)
						.limit(10)
						.sorted(Comparator.comparing(Libro::getPrezzo))
						.forEach(System.out::println);;
	}
	
	public static void query8() { // Conteggio per ogni libro venduto
		System.out.println("---------------");
		System.out.println("#Query 8");
		
		List<Libro> lista = Stream.generate(Libro::gen).limit(10).collect(Collectors.toList());
		
		lista.stream()
			.map(x -> x.getTitolo())
			.distinct()
			.peek(t -> System.out.print("Titolo: " + t + " "))
			.forEach(t -> System.out.println(
					lista.stream()
					.filter(x -> x.getTitolo().equals(t))
					.count()					
			));
	}
	
	public static void query9() { // Stampa i libri raggruppati per categoria (senza groupingBy)
		System.out.println("---------------");
		System.out.println("#Query 9");
		
		List<Libro> lista = Stream.generate(Libro::gen).limit(10).collect(Collectors.toList());

		lista.stream()
			.map(c -> c.getCategoria())
			.distinct()
			.peek(c -> System.out.println("Categoria : " + c))
			.forEach(c -> lista.stream()
						.filter(e -> e.getCategoria().equals(c))
						.forEach(System.out::println)
					);
	}
	
	public static List<Libro> query10() { //Generare libri Harry Potter da 1 a 7 con costo 15€
		System.out.println("---------------");
		System.out.println("#Query 10");
		List<Libro> lista = IntStream.rangeClosed(1, 7)
				.mapToObj(i -> new Libro("Harry Potter " + i, Libro.Categoria.FANTASY, 15))
				.collect(Collectors.toList());
		System.out.println(lista);
		return lista;
	}

	public static List<Libro> query11(){ // Sfruttando il metodo precedente, ottenere la lista di libri e mescolarla in ordine casuale
		System.out.println("---------------");
		System.out.println("#Query 11");
		List<Libro> listaOrdinata = query10();
		
		List<Libro> listaDisordinata = 
				IntStream.generate(() -> (int) (Math.random()*listaOrdinata.size()))
				.distinct()
				.limit(listaOrdinata.size())
				.mapToObj(i -> listaOrdinata.get(i))
				.collect(Collectors.toList());

		System.out.println(listaDisordinata);
		return listaDisordinata;
						
	}

	public static void query12() { // Data una lista di libri, stampare il primo che ha un prezzo maggiore del precedente (Funzione Pura)
		System.out.println("---------------");
		System.out.println("#Query 12");
		
		List<Libro> lista = Stream.generate(Libro::gen).limit(10).collect(Collectors.toList());
		System.out.println(lista);
		
		Optional<Libro> l = IntStream.rangeClosed(1, lista.size())
			.filter(i -> lista.get(i).getPrezzo()>lista.get(i-1).getPrezzo())
			.mapToObj(i -> lista.get(i))
			.findAny();
		
		if(l.isPresent())
			System.out.println(l.get());
	}

	public static void query14() {
		System.out.println("---------------");
		System.out.println("#Query 14");
		
		List<Libro> lista = Stream.generate(Libro::gen).limit(10).collect(Collectors.toList());

	}
	
	public static void Pierpaolo() {
		List<Integer> l = new ArrayList<Integer>(List.of(10, 5, 20, 30, 15, 50));
		l.set(l.size()-1, 100);
		System.out.println(l);
		
		List<Integer> res = IntStream.rangeClosed(0, l.size()-1)
			.mapToObj(i -> l.get(((i+l.size()-1)%l.size())))
			.collect(Collectors.toList());
		
		System.out.println(res);
	}
	
	

}
