
public class MainArmeria {

	public static void main(String[] args) {
		Spada s1 = Emporio.compraSpadaFullOptional();
		Spada s2 = Emporio.compraSpadaPesanteSpettraleAvvelenata();
		Spada s3 = Emporio.compraSpadaInfuocatissima();
		
		System.out.println(s1);
		System.out.println(s2);
		System.out.println(s3);
	}

}
