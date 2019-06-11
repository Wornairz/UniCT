package esempio2;

import java.util.Arrays;

public class MainLambda {

	public static void main(String[] args) {
		Plotter pl = new Plotter(Arrays.asList(1.5, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0));
		pl.plot(d -> Math.sqrt(d));
		pl.plot(d -> Math.pow(d, 2));
		pl.plot(Math::cos);
		pl.plot(Math::sin);
	}
}
