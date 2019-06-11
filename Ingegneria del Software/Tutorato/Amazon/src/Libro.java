
public class Libro {
	private String titolo;
	private Categoria categoria;
	private int prezzo;
	
	static enum Categoria{
		FANTASY,
		CYBERPUNK,
		THRILLER
	}

	private static Libro[] prodPool = new Libro[] {
			new Libro("Leviathan", Categoria.FANTASY, 20),
			new Libro("Trono di Spade", Categoria.FANTASY, 40),
			new Libro("Signore degli Anelli", Categoria.FANTASY, 25),
			

			new Libro("Neuromante", Categoria.CYBERPUNK, 15),
			new Libro("Monnalisa Cyberpunk", Categoria.CYBERPUNK, 12),
			new Libro("Mirrorshades", Categoria.CYBERPUNK, 10),
			
			new Libro("Profondo Blu", Categoria.THRILLER, 8),
			new Libro("Invasion", Categoria.THRILLER, 12),
			new Libro("La Torre Nera", Categoria.THRILLER, 18)
		};
	
	public static Libro gen() {
		return prodPool[(int) (Math.random()*prodPool.length)];
		//return prodPool[(int) (new Random().nextInt()%prodPool.length)];
	}
	
	public Libro(String titolo, Categoria categoria, int prezzo) {
		this.titolo = titolo;
		this.categoria = categoria;
		this.prezzo = prezzo;
	}

	public String getTitolo() {
		return titolo;
	}

	public void setTitolo(String titolo) {
		this.titolo = titolo;
	}

	public int getPrezzo() {
		return prezzo;
	}

	public void setPrezzo(int prezzo) {
		this.prezzo = prezzo;
	}

	@Override
	public String toString() {
		return "Libro [titolo=" + titolo + ", categoria=" + categoria + ", prezzo=" + prezzo + "€]\n";
	}

	public Categoria getCategoria() {
		return categoria;
	}

	public static Libro[] getProdPool() {
		return prodPool;
	}
	
}
