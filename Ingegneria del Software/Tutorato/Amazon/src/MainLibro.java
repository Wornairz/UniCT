import java.util.Comparator;
import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;
import java.util.stream.IntStream;
import java.util.stream.Stream;

public class MainLibro {

	public static void main(String[] args) {
		//query0();
		//query1();
		//query2();
		//query3();
		//query4();
		//query5();
		//query6();
		//query7();
		//query8();
		query9();
		//query10();
	}
	
	public static void query0() {
		Stream.generate(Libro::gen).limit(10).forEach(System.out::println);
	}
	
	public static void query1() { //Contare libri CYBERPUNK
		System.out.println("---------------");
		System.out.println("#Query 1");
		long cnt = Stream.generate(Libro::gen).limit(10).filter(x -> x.getCategoria() == Libro.Categoria.CYBERPUNK).count();
		System.out.println("I libri CYBERPUNK SONO " + cnt);
	}
	

	public static List<Libro> query2() { //Lista libri CYBERPUNK o FANTASY
		System.out.println("---------------");
		System.out.println("#Query 2");
		List<Libro> listaLibri = Stream.generate(Libro::gen)
				.limit(10)
				.filter(x -> x.getCategoria() == Libro.Categoria.CYBERPUNK || x.getCategoria() == Libro.Categoria.FANTASY)
				//.map(x -> x.getTitolo())
				.collect(Collectors.toList());
		System.out.println(listaLibri);
		return listaLibri;
	}

	public static void query3() { //Somma dei costi di tutti i libri
		System.out.println("---------------");
		System.out.println("#Query 3");
		Optional<Integer> sum = Stream.generate(Libro::gen)
						.limit(10)
						.map(x -> x.getPrezzo())
						.reduce(Integer::sum);
		if(sum.isPresent()) {
			System.out.println("La somma è " + sum.get());
		}
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
						.filter(x -> x.getPrezzo()>=10)
						.filter(x -> x.getPrezzo()<=15)
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
		
		return lista;
	}
}
