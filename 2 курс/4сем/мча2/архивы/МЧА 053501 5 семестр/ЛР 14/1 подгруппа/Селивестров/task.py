import methods

h = (methods.B - methods.A) / 200
tau = 0.2 * (h ** 2) / methods.k

methods.explicit_method_1(h, tau, build_plot=True)
methods.explicit_method_2(h, tau, build_plot=True)
methods.implicit_method_1(h, tau, build_plot=True)
methods.implicit_method_2(h, tau, build_plot=True)