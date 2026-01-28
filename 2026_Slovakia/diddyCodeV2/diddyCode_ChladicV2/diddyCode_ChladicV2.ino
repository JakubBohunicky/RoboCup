const float motionAngles[361][4] = {
  { 0.353555, 0.353552, -0.353555, -0.353552 },
  { 0.347331, 0.359669, -0.347331, -0.359669 },
  { 0.341001, 0.365675, -0.341001, -0.365675 },
  { 0.334567, 0.371571, -0.334567, -0.371571 },
  { 0.328031, 0.377353, -0.328031, -0.377353 },
  { 0.321395, 0.383021, -0.321395, -0.383021 },
  { 0.314662, 0.388572, -0.314662, -0.388572 },
  { 0.307832, 0.394004, -0.307832, -0.394004 },
  { 0.300909, 0.399317, -0.300909, -0.399317 },
  { 0.293894, 0.404507, -0.293894, -0.404507 },
  { 0.28679, 0.409575, -0.28679, -0.409575 },
  { 0.279598, 0.414518, -0.279598, -0.414518 },
  { 0.272321, 0.419334, -0.272321, -0.419334 },
  { 0.264961, 0.424023, -0.264961, -0.424023 },
  { 0.257521, 0.428583, -0.257521, -0.428583 },
  { 0.250002, 0.433012, -0.250002, -0.433012 },
  { 0.242407, 0.437309, -0.242407, -0.437309 },
  { 0.234738, 0.441473, -0.234738, -0.441473 },
  { 0.226997, 0.445502, -0.226997, -0.445502 },
  { 0.219187, 0.449396, -0.219187, -0.449396 },
  { 0.211311, 0.453153, -0.211311, -0.453153 },
  { 0.20337, 0.456772, -0.20337, -0.456772 },
  { 0.195368, 0.460252, -0.195368, -0.460252 },
  { 0.187305, 0.463591, -0.187305, -0.463591 },
  { 0.179186, 0.466789, -0.179186, -0.466789 },
  { 0.171012, 0.469846, -0.171012, -0.469846 },
  { 0.162786, 0.472759, -0.162786, -0.472759 },
  { 0.154511, 0.475528, -0.154511, -0.475528 },
  { 0.146188, 0.478152, -0.146188, -0.478152 },
  { 0.137821, 0.48063, -0.137821, -0.48063 },
  { 0.129412, 0.482962, -0.129412, -0.482962 },
  { 0.120963, 0.485147, -0.120963, -0.485147 },
  { 0.112478, 0.487185, -0.112478, -0.487185 },
  { 0.103958, 0.489073, -0.103958, -0.489073 },
  { 0.0954067, 0.490813, -0.0954067, -0.490813 },
  { 0.0868263, 0.492403, -0.0868263, -0.492403 },
  { 0.0782195, 0.493844, -0.0782195, -0.493844 },
  { 0.0695888, 0.495134, -0.0695888, -0.495134 },
  { 0.0609369, 0.496273, -0.0609369, -0.496273 },
  { 0.0522665, 0.497261, -0.0522665, -0.497261 },
  { 0.0435801, 0.498097, -0.0435801, -0.498097 },
  { 0.0348805, 0.498782, -0.0348805, -0.498782 },
  { 0.0261703, 0.499315, -0.0261703, -0.499315 },
  { 0.0174521, 0.499695, -0.0174521, -0.499695 },
  { 0.00872852, 0.499924, -0.00872852, -0.499924 },
  { 2.32189e-06, 0.5, -2.32189e-06, -0.5 },
  { -0.00872387, 0.499924, 0.00872387, -0.499924 },
  { -0.0174474, 0.499696, 0.0174474, -0.499696 },
  { -0.0261656, 0.499315, 0.0261656, -0.499315 },
  { -0.0348759, 0.498782, 0.0348759, -0.498782 },
  { -0.0435755, 0.498098, 0.0435755, -0.498098 },
  { -0.0522619, 0.497261, 0.0522619, -0.497261 },
  { -0.0609323, 0.496273, 0.0609323, -0.496273 },
  { -0.0695842, 0.495134, 0.0695842, -0.495134 },
  { -0.0782149, 0.493845, 0.0782149, -0.493845 },
  { -0.0868217, 0.492404, 0.0868217, -0.492404 },
  { -0.0954021, 0.490814, 0.0954021, -0.490814 },
  { -0.103953, 0.489074, 0.103953, -0.489074 },
  { -0.112473, 0.487186, 0.112473, -0.487186 },
  { -0.120959, 0.485148, 0.120959, -0.485148 },
  { -0.129407, 0.482964, 0.129407, -0.482964 },
  { -0.137816, 0.480632, 0.137816, -0.480632 },
  { -0.146184, 0.478153, 0.146184, -0.478153 },
  { -0.154506, 0.475529, 0.154506, -0.475529 },
  { -0.162782, 0.47276, 0.162782, -0.47276 },
  { -0.171008, 0.469847, 0.171008, -0.469847 },
  { -0.179182, 0.466791, 0.179182, -0.466791 },
  { -0.187301, 0.463593, 0.187301, -0.463593 },
  { -0.195363, 0.460253, 0.195363, -0.460253 },
  { -0.203366, 0.456774, 0.203366, -0.456774 },
  { -0.211307, 0.453155, 0.211307, -0.453155 },
  { -0.219183, 0.449398, 0.219183, -0.449398 },
  { -0.226993, 0.445504, 0.226993, -0.445504 },
  { -0.234734, 0.441475, 0.234734, -0.441475 },
  { -0.242403, 0.437311, 0.242403, -0.437311 },
  { -0.249998, 0.433014, 0.249998, -0.433014 },
  { -0.257517, 0.428585, 0.257517, -0.428585 },
  { -0.264957, 0.424025, 0.264957, -0.424025 },
  { -0.272317, 0.419337, 0.272317, -0.419337 },
  { -0.279594, 0.41452, 0.279594, -0.41452 },
  { -0.286786, 0.409577, 0.286786, -0.409577 },
  { -0.293891, 0.40451, 0.293891, -0.40451 },
  { -0.300905, 0.399319, 0.300905, -0.399319 },
  { -0.307829, 0.394007, 0.307829, -0.394007 },
  { -0.314658, 0.388575, 0.314658, -0.388575 },
  { -0.321392, 0.383024, 0.321392, -0.383024 },
  { -0.328028, 0.377356, 0.328028, -0.377356 },
  { -0.334563, 0.371574, 0.334563, -0.371574 },
  { -0.340997, 0.365679, 0.340997, -0.365679 },
  { -0.347327, 0.359672, 0.347327, -0.359672 },
  { -0.353553, 0.353553, 0.353553, -0.353553 },
  { -0.35967, 0.347329, 0.35967, -0.347329 },
  { -0.365677, 0.340999, 0.365677, -0.340999 },
  { -0.371572, 0.334565, 0.371572, -0.334565 },
  { -0.377355, 0.32803, 0.377355, -0.32803 },
  { -0.383022, 0.321394, 0.383022, -0.321394 },
  { -0.388573, 0.31466, 0.388573, -0.31466 },
  { -0.394005, 0.307831, 0.394005, -0.307831 },
  { -0.399318, 0.300908, 0.399318, -0.300908 },
  { -0.404508, 0.293893, 0.404508, -0.293893 },
  { -0.409576, 0.286788, 0.409576, -0.286788 },
  { -0.414519, 0.279597, 0.414519, -0.279597 },
  { -0.419335, 0.27232, 0.419335, -0.27232 },
  { -0.424024, 0.26496, 0.424024, -0.26496 },
  { -0.428584, 0.257519, 0.428584, -0.257519 },
  { -0.433013, 0.25, 0.433013, -0.25 },
  { -0.43731, 0.242405, 0.43731, -0.242405 },
  { -0.441474, 0.234736, 0.441474, -0.234736 },
  { -0.445503, 0.226995, 0.445503, -0.226995 },
  { -0.449397, 0.219186, 0.449397, -0.219186 },
  { -0.453154, 0.211309, 0.453154, -0.211309 },
  { -0.456773, 0.203368, 0.456773, -0.203368 },
  { -0.460252, 0.195366, 0.460252, -0.195366 },
  { -0.463592, 0.187303, 0.463592, -0.187303 },
  { -0.46679, 0.179184, 0.46679, -0.179184 },
  { -0.469846, 0.17101, 0.469846, -0.17101 },
  { -0.472759, 0.162784, 0.472759, -0.162784 },
  { -0.475528, 0.154509, 0.475528, -0.154509 },
  { -0.478152, 0.146186, 0.478152, -0.146186 },
  { -0.480631, 0.137819, 0.480631, -0.137819 },
  { -0.482963, 0.12941, 0.482963, -0.12941 },
  { -0.485148, 0.120961, 0.485148, -0.120961 },
  { -0.487185, 0.112476, 0.487185, -0.112476 },
  { -0.489074, 0.103956, 0.489074, -0.103956 },
  { -0.490814, 0.0954047, 0.490814, -0.0954047 },
  { -0.492404, 0.0868243, 0.492404, -0.0868243 },
  { -0.493844, 0.0782175, 0.493844, -0.0782175 },
  { -0.495134, 0.0695868, 0.495134, -0.0695868 },
  { -0.496273, 0.0609349, 0.496273, -0.0609349 },
  { -0.497261, 0.0522645, 0.497261, -0.0522645 },
  { -0.498097, 0.0435782, 0.498097, -0.0435782 },
  { -0.498782, 0.0348785, 0.498782, -0.0348785 },
  { -0.499315, 0.0261683, 0.499315, -0.0261683 },
  { -0.499695, 0.0174501, 0.499695, -0.0174501 },
  { -0.499924, 0.00872653, 0.499924, -0.00872653 },
  { -0.5, 3.31699e-07, 0.5, -3.31699e-07 },
  { -0.499924, -0.00872586, 0.499924, 0.00872586 },
  { -0.499695, -0.0174494, 0.499695, 0.0174494 },
  { -0.499315, -0.0261676, 0.499315, 0.0261676 },
  { -0.498782, -0.0348779, 0.498782, 0.0348779 },
  { -0.498097, -0.0435775, 0.498097, 0.0435775 },
  { -0.497261, -0.0522639, 0.497261, 0.0522639 },
  { -0.496273, -0.0609343, 0.496273, 0.0609343 },
  { -0.495134, -0.0695862, 0.495134, 0.0695862 },
  { -0.493844, -0.0782168, 0.493844, 0.0782168 },
  { -0.492404, -0.0868237, 0.492404, 0.0868237 },
  { -0.490814, -0.0954041, 0.490814, 0.0954041 },
  { -0.489074, -0.103955, 0.489074, 0.103955 },
  { -0.487185, -0.112475, 0.487185, 0.112475 },
  { -0.485148, -0.120961, 0.485148, 0.120961 },
  { -0.482963, -0.129409, 0.482963, 0.129409 },
  { -0.480631, -0.137818, 0.480631, 0.137818 },
  { -0.478153, -0.146185, 0.478153, 0.146185 },
  { -0.475528, -0.154508, 0.475528, 0.154508 },
  { -0.472759, -0.162784, 0.472759, 0.162784 },
  { -0.469846, -0.17101, 0.469846, 0.17101 },
  { -0.46679, -0.179184, 0.46679, 0.179184 },
  { -0.463592, -0.187303, 0.463592, 0.187303 },
  { -0.460253, -0.195365, 0.460253, 0.195365 },
  { -0.456773, -0.203368, 0.456773, 0.203368 },
  { -0.453154, -0.211309, 0.453154, 0.211309 },
  { -0.449397, -0.219185, 0.449397, 0.219185 },
  { -0.445504, -0.226995, 0.445504, 0.226995 },
  { -0.441474, -0.234735, 0.441474, 0.234735 },
  { -0.43731, -0.242404, 0.43731, 0.242404 },
  { -0.433013, -0.25, 0.433013, 0.25 },
  { -0.428584, -0.257519, 0.428584, 0.257519 },
  { -0.424024, -0.264959, 0.424024, 0.264959 },
  { -0.419336, -0.272319, 0.419336, 0.272319 },
  { -0.414519, -0.279596, 0.414519, 0.279596 },
  { -0.409576, -0.286788, 0.409576, 0.286788 },
  { -0.404509, -0.293892, 0.404509, 0.293892 },
  { -0.399318, -0.300907, 0.399318, 0.300907 },
  { -0.394006, -0.30783, 0.394006, 0.30783 },
  { -0.388573, -0.31466, 0.388573, 0.31466 },
  { -0.383023, -0.321393, 0.383023, 0.321393 },
  { -0.377355, -0.328029, 0.377355, 0.328029 },
  { -0.371573, -0.334565, 0.371573, 0.334565 },
  { -0.365677, -0.340999, 0.365677, 0.340999 },
  { -0.35967, -0.347329, 0.35967, 0.347329 },
  { -0.353554, -0.353553, 0.353554, 0.353553 },
  { -0.34733, -0.359669, 0.34733, 0.359669 },
  { -0.341, -0.365676, 0.341, 0.365676 },
  { -0.334566, -0.371572, 0.334566, 0.371572 },
  { -0.32803, -0.377354, 0.32803, 0.377354 },
  { -0.321394, -0.383022, 0.321394, 0.383022 },
  { -0.314661, -0.388573, 0.314661, 0.388573 },
  { -0.307831, -0.394005, 0.307831, 0.394005 },
  { -0.300908, -0.399317, 0.300908, 0.399317 },
  { -0.293893, -0.404508, 0.293893, 0.404508 },
  { -0.286789, -0.409576, 0.286789, 0.409576 },
  { -0.279597, -0.414518, 0.279597, 0.414518 },
  { -0.27232, -0.419335, 0.27232, 0.419335 },
  { -0.26496, -0.424024, 0.26496, 0.424024 },
  { -0.25752, -0.428583, 0.25752, 0.428583 },
  { -0.250001, -0.433012, 0.250001, 0.433012 },
  { -0.242405, -0.437309, 0.242405, 0.437309 },
  { -0.234736, -0.441473, 0.234736, 0.441473 },
  { -0.226996, -0.445503, 0.226996, 0.445503 },
  { -0.219186, -0.449397, 0.219186, 0.449397 },
  { -0.21131, -0.453154, 0.21131, 0.453154 },
  { -0.203369, -0.456772, 0.203369, 0.456772 },
  { -0.195366, -0.460252, 0.195366, 0.460252 },
  { -0.187304, -0.463592, 0.187304, 0.463592 },
  { -0.179185, -0.46679, 0.179185, 0.46679 },
  { -0.171011, -0.469846, 0.171011, 0.469846 },
  { -0.162785, -0.472759, 0.162785, 0.472759 },
  { -0.154509, -0.475528, 0.154509, 0.475528 },
  { -0.146187, -0.478152, 0.146187, 0.478152 },
  { -0.13782, -0.480631, 0.13782, 0.480631 },
  { -0.12941, -0.482963, 0.12941, 0.482963 },
  { -0.120962, -0.485148, 0.120962, 0.485148 },
  { -0.112476, -0.487185, 0.112476, 0.487185 },
  { -0.103957, -0.489074, 0.103957, 0.489074 },
  { -0.0954054, -0.490813, 0.0954054, 0.490813 },
  { -0.086825, -0.492404, 0.086825, 0.492404 },
  { -0.0782181, -0.493844, 0.0782181, 0.493844 },
  { -0.0695875, -0.495134, 0.0695875, 0.495134 },
  { -0.0609356, -0.496273, 0.0609356, 0.496273 },
  { -0.0522652, -0.497261, 0.0522652, 0.497261 },
  { -0.0435788, -0.498097, 0.0435788, 0.498097 },
  { -0.0348792, -0.498782, 0.0348792, 0.498782 },
  { -0.0261689, -0.499315, 0.0261689, 0.499315 },
  { -0.0174507, -0.499695, 0.0174507, 0.499695 },
  { -0.00872719, -0.499924, 0.00872719, 0.499924 },
  { -9.95096e-07, -0.5, 9.95096e-07, 0.5 },
  { 0.0087252, -0.499924, -0.0087252, 0.499924 },
  { 0.0174487, -0.499695, -0.0174487, 0.499695 },
  { 0.026167, -0.499315, -0.026167, 0.499315 },
  { 0.0348772, -0.498782, -0.0348772, 0.498782 },
  { 0.0435768, -0.498097, -0.0435768, 0.498097 },
  { 0.0522632, -0.497261, -0.0522632, 0.497261 },
  { 0.0609336, -0.496273, -0.0609336, 0.496273 },
  { 0.0695855, -0.495134, -0.0695855, 0.495134 },
  { 0.0782162, -0.493844, -0.0782162, 0.493844 },
  { 0.086823, -0.492404, -0.086823, 0.492404 },
  { 0.0954034, -0.490814, -0.0954034, 0.490814 },
  { 0.103955, -0.489074, -0.103955, 0.489074 },
  { 0.112474, -0.487185, -0.112474, 0.487185 },
  { 0.12096, -0.485148, -0.12096, 0.485148 },
  { 0.129408, -0.482963, -0.129408, 0.482963 },
  { 0.137818, -0.480631, -0.137818, 0.480631 },
  { 0.146185, -0.478153, -0.146185, 0.478153 },
  { 0.154507, -0.475529, -0.154507, 0.475529 },
  { 0.162783, -0.47276, -0.162783, 0.47276 },
  { 0.171009, -0.469847, -0.171009, 0.469847 },
  { 0.179183, -0.466791, -0.179183, 0.466791 },
  { 0.187302, -0.463592, -0.187302, 0.463592 },
  { 0.195364, -0.460253, -0.195364, 0.460253 },
  { 0.203367, -0.456773, -0.203367, 0.456773 },
  { 0.211308, -0.453154, -0.211308, 0.453154 },
  { 0.219185, -0.449398, -0.219185, 0.449398 },
  { 0.226994, -0.445504, -0.226994, 0.445504 },
  { 0.234735, -0.441474, -0.234735, 0.441474 },
  { 0.242404, -0.43731, -0.242404, 0.43731 },
  { 0.249999, -0.433013, -0.249999, 0.433013 },
  { 0.257518, -0.428584, -0.257518, 0.428584 },
  { 0.264959, -0.424025, -0.264959, 0.424025 },
  { 0.272318, -0.419336, -0.272318, 0.419336 },
  { 0.279595, -0.414519, -0.279595, 0.414519 },
  { 0.286787, -0.409577, -0.286787, 0.409577 },
  { 0.293892, -0.404509, -0.293892, 0.404509 },
  { 0.300907, -0.399319, -0.300907, 0.399319 },
  { 0.30783, -0.394006, -0.30783, 0.394006 },
  { 0.314659, -0.388574, -0.314659, 0.388574 },
  { 0.321393, -0.383023, -0.321393, 0.383023 },
  { 0.328029, -0.377356, -0.328029, 0.377356 },
  { 0.334564, -0.371573, -0.334564, 0.371573 },
  { 0.340998, -0.365678, -0.340998, 0.365678 },
  { 0.347328, -0.359671, -0.347328, 0.359671 },
  { 0.353552, -0.353554, -0.353552, 0.353554 },
  { 0.359669, -0.34733, -0.359669, 0.34733 },
  { 0.365676, -0.341, -0.365676, 0.341 },
  { 0.371572, -0.334566, -0.371572, 0.334566 },
  { 0.377354, -0.328031, -0.377354, 0.328031 },
  { 0.383021, -0.321395, -0.383021, 0.321395 },
  { 0.388572, -0.314661, -0.388572, 0.314661 },
  { 0.394005, -0.307832, -0.394005, 0.307832 },
  { 0.399317, -0.300909, -0.399317, 0.300909 },
  { 0.404508, -0.293894, -0.404508, 0.293894 },
  { 0.409575, -0.286789, -0.409575, 0.286789 },
  { 0.414518, -0.279598, -0.414518, 0.279598 },
  { 0.419335, -0.272321, -0.419335, 0.272321 },
  { 0.424023, -0.264961, -0.424023, 0.264961 },
  { 0.428583, -0.25752, -0.428583, 0.25752 },
  { 0.433012, -0.250001, -0.433012, 0.250001 },
  { 0.437309, -0.242406, -0.437309, 0.242406 },
  { 0.441473, -0.234737, -0.441473, 0.234737 },
  { 0.445503, -0.226997, -0.445503, 0.226997 },
  { 0.449396, -0.219187, -0.449396, 0.219187 },
  { 0.453153, -0.21131, -0.453153, 0.21131 },
  { 0.456772, -0.20337, -0.456772, 0.20337 },
  { 0.460252, -0.195367, -0.460252, 0.195367 },
  { 0.463591, -0.187305, -0.463591, 0.187305 },
  { 0.46679, -0.179185, -0.46679, 0.179185 },
  { 0.469846, -0.171011, -0.469846, 0.171011 },
  { 0.472759, -0.162786, -0.472759, 0.162786 },
  { 0.475528, -0.15451, -0.475528, 0.15451 },
  { 0.478152, -0.146187, -0.478152, 0.146187 },
  { 0.48063, -0.13782, -0.48063, 0.13782 },
  { 0.482963, -0.129411, -0.482963, 0.129411 },
  { 0.485147, -0.120962, -0.485147, 0.120962 },
  { 0.487185, -0.112477, -0.487185, 0.112477 },
  { 0.489073, -0.103957, -0.489073, 0.103957 },
  { 0.490813, -0.095406, -0.490813, 0.095406 },
  { 0.492404, -0.0868256, -0.492404, 0.0868256 },
  { 0.493844, -0.0782188, -0.493844, 0.0782188 },
  { 0.495134, -0.0695881, -0.495134, 0.0695881 },
  { 0.496273, -0.0609363, -0.496273, 0.0609363 },
  { 0.497261, -0.0522658, -0.497261, 0.0522658 },
  { 0.498097, -0.0435795, -0.498097, 0.0435795 },
  { 0.498782, -0.0348799, -0.498782, 0.0348799 },
  { 0.499315, -0.0261696, -0.499315, 0.0261696 },
  { 0.499695, -0.0174514, -0.499695, 0.0174514 },
  { 0.499924, -0.00872785, -0.499924, 0.00872785 },
  { 0.5, -1.65849e-06, -0.5, 1.65849e-06 },
  { 0.499924, 0.00872454, -0.499924, -0.00872454 },
  { 0.499695, 0.0174481, -0.499695, -0.0174481 },
  { 0.499315, 0.0261663, -0.499315, -0.0261663 },
  { 0.498782, 0.0348766, -0.498782, -0.0348766 },
  { 0.498098, 0.0435762, -0.498098, -0.0435762 },
  { 0.497261, 0.0522625, -0.497261, -0.0522625 },
  { 0.496273, 0.060933, -0.496273, -0.060933 },
  { 0.495134, 0.0695848, -0.495134, -0.0695848 },
  { 0.493844, 0.0782155, -0.493844, -0.0782155 },
  { 0.492404, 0.0868224, -0.492404, -0.0868224 },
  { 0.490814, 0.0954028, -0.490814, -0.0954028 },
  { 0.489074, 0.103954, -0.489074, -0.103954 },
  { 0.487185, 0.112474, -0.487185, -0.112474 },
  { 0.485148, 0.120959, -0.485148, -0.120959 },
  { 0.482963, 0.129408, -0.482963, -0.129408 },
  { 0.480631, 0.137817, -0.480631, -0.137817 },
  { 0.478153, 0.146184, -0.478153, -0.146184 },
  { 0.475529, 0.154507, -0.475529, -0.154507 },
  { 0.47276, 0.162782, -0.47276, -0.162782 },
  { 0.469847, 0.171008, -0.469847, -0.171008 },
  { 0.466791, 0.179182, -0.466791, -0.179182 },
  { 0.463593, 0.187302, -0.463593, -0.187302 },
  { 0.460253, 0.195364, -0.460253, -0.195364 },
  { 0.456773, 0.203367, -0.456773, -0.203367 },
  { 0.453155, 0.211307, -0.453155, -0.211307 },
  { 0.449398, 0.219184, -0.449398, -0.219184 },
  { 0.445504, 0.226994, -0.445504, -0.226994 },
  { 0.441475, 0.234734, -0.441475, -0.234734 },
  { 0.437311, 0.242403, -0.437311, -0.242403 },
  { 0.433014, 0.249998, -0.433014, -0.249998 },
  { 0.428585, 0.257517, -0.428585, -0.257517 },
  { 0.424025, 0.264958, -0.424025, -0.264958 },
  { 0.419336, 0.272318, -0.419336, -0.272318 },
  { 0.41452, 0.279595, -0.41452, -0.279595 },
  { 0.409577, 0.286787, -0.409577, -0.286787 },
  { 0.40451, 0.293891, -0.40451, -0.293891 },
  { 0.399319, 0.300906, -0.399319, -0.300906 },
  { 0.394007, 0.307829, -0.394007, -0.307829 },
  { 0.388574, 0.314659, -0.388574, -0.314659 },
  { 0.383023, 0.321392, -0.383023, -0.321392 },
  { 0.377356, 0.328028, -0.377356, -0.328028 },
  { 0.371574, 0.334564, -0.371574, -0.334564 },
  { 0.365678, 0.340998, -0.365678, -0.340998 },
  { 0.359671, 0.347328, -0.359671, -0.347328 },
  { 0, 0, 0, 0 }
};


#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <math.h>
#include <utility/imumaths.h>
#include <Pixy2.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define STOP_MOTORS false
#define DISPLAY_DEBUG false


#define ballEffectiveInputClosest 2500
#define ballEffectiveInputFurthes 2100

// uint32_t cycleTime = 0;

Pixy2 pixy;

#define P 4  //3
#define I 0
#define D 6 //5

#define BNO055_SAMPLERATE_DELAY_MS (1);
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);

#define OLED_WIDTH 128
#define OLED_HEIGHT 32

#define OLED_ADDR 0x3c

//pomer motorov
#define MA_OFFSET 0.75
#define MB_OFFSET 1.25
#define MC_OFFSET 0.75
#define MD_OFFSET 1.25

// #define TCAADDR 0x70
// #define TCA_COMPASS 0
// #define TCA_IR_FRONT 1
// #define TCA_IR_BACK 2
// #define TCA_IR_V3 3

#define IR_I2C_ADDRESS 0x10
#define IR_REGISTER_ANGLE_AND_DISTANCE 0x00


Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT);

float outPid;
float error;
float oldError;
float sumI;

float spdA;
float spdB;
float spdC;
float spdD;

unsigned long kickTime;
int lineFeature = 0;

unsigned long backwardTime = 0;

int speed = 400;  //350 600
uint16_t maxLineSpeed = 600;

//dida
//rychlost cuvania
int speedBack = 150;  //200
//dida

int line;
int lineDebug = 999;
int oldLine = 180;
unsigned long lineTouchTime = 0;


bool goForward = true;

int16_t ballAngle = 999;
uint16_t ballDistance = 0;
float ballDistanceFinalAngleOffset = 1;
float ballFilteredDistance = 0;
uint16_t ballRawDistance;

#define multiplexerPin1 22  //ir multiplexer pins
#define multiplexerPin2 24
#define multiplexerPin3 26
#define multiplexerPin4 28
#define multiplexerIn A12
#define multiplexerIn1 A13
#define multiplexerIn2 A15

#define motorDPWM 3   //PWM pin motor A
#define motorDINB 25  //INA pin motor A
#define motorDINA 27  //INB pin motor A

#define motorAPWM 8 //5   //PWM pin motor B
#define motorAINB 11 //29  //INA pin motor B
#define motorAINA 12  //33  //INB pin motor B

#define motorCPWM 7   //PWM pin motor C
#define motorCINB 37  //INA pin motor C
#define motorCINA 39  //INB pin motor C

#define motorBPWM 9   //PWM pin motor D
#define motorBINB 43  //INA pin motor D
#define motorBINA 45  //INB pin motor D

const int outputArray[16][4] = {
  { 0, 0, 0, 0 },
  { 0, 0, 0, 1 },
  { 0, 0, 1, 0 },
  { 0, 0, 1, 1 },
  { 0, 1, 0, 0 },
  { 0, 1, 0, 1 },
  { 0, 1, 1, 0 },
  { 0, 1, 1, 1 },
  { 1, 0, 0, 0 },
  { 1, 0, 0, 1 },
  { 1, 0, 1, 0 },
  { 1, 0, 1, 1 },
  { 1, 1, 0, 0 },
  { 1, 1, 0, 1 },
  { 1, 1, 1, 0 },
  { 1, 1, 1, 1 }
};

const int outputArray2[16][4] = {
  { 0, 0, 0, 0 },
  { 0, 0, 0, 1 },
  { 1, 1, 0, 0 },
  { 0, 0, 1, 0 },
  { 1, 1, 0, 1 },
  { 0, 0, 1, 1 },
  { 1, 1, 1, 0 },
  { 0, 1, 0, 0 },
  { 1, 1, 1, 1 },
  { 0, 1, 0, 1 },
  { 0, 1, 1, 0 },
  { 0, 1, 1, 1 },
  { 1, 0, 0, 0 },
  { 1, 0, 0, 1 },
  { 1, 0, 1, 0 },
  { 1, 0, 1, 1 }

};

const float sensorAngles[16] = { 90, 60, 45, 30, 15, 360, 345, 330, 315, 300, 270, 240, 210, 180, 150, 120 };
const float lightSensorAngles[32] = { 343.125, 354.375, 5.625, 16.875, 28.125, 39.375, 50.625, 61.875, 106.875, 95.625, 84.375, 73.125, 118.125, 129.375, 140.625, 151.875, 163.125, 174.375, 185.625, 196.875, 208.125, 219.375, 230.625, 241.875, 253.125, 264.375, 275.625, 286.875, 298.125, 309.375, 320.625 };
const int lightTreshold[32] = {
  159, 484, 133, 549, 139, 565, 142, 643,
  565, 578, 144, 558, 155, 592, 156, 625,
  157, 547, 141, 600, 155, 611, 158, -7,
  160, 609, 157, 625, 162, 635, 163, 193
};


void define_motors() {
  pinMode(motorAPWM, OUTPUT);  //motor A PWM
  pinMode(motorAINA, OUTPUT);  //motor A INA
  pinMode(motorAINB, OUTPUT);  //motor A INB

  pinMode(motorBPWM, OUTPUT);  //motor B PWM
  pinMode(motorBINA, OUTPUT);  //motor B INA
  pinMode(motorBINB, OUTPUT);  //motor B INB

  pinMode(motorCPWM, OUTPUT);  //motor C PWM
  pinMode(motorCINA, OUTPUT);  //motor C INA
  pinMode(motorCINB, OUTPUT);  //motor C INB

  pinMode(motorDPWM, OUTPUT);  //motor D PWM
  pinMode(motorDINA, OUTPUT);  //motor D INA
  pinMode(motorDINB, OUTPUT);  //motor D INB
}


void define_irMultiplexer() {
  pinMode(multiplexerPin1, OUTPUT);
  pinMode(multiplexerPin2, OUTPUT);
  pinMode(multiplexerPin3, OUTPUT);
  pinMode(multiplexerPin4, OUTPUT);
  pinMode(multiplexerIn, INPUT);
  pinMode(multiplexerIn1, INPUT);
  pinMode(multiplexerIn2, INPUT);
}

void motor(byte id, float spd) {

#if !STOP_MOTORS
  switch (id) {
    case 1:
      analogWrite(motorAPWM, spd > 0 ? spd : -spd);
      digitalWrite(motorAINA, spd > 0 ? HIGH : LOW);
      digitalWrite(motorAINB, spd > 0 ? LOW : HIGH);
      break;
    case 2:
      analogWrite(motorBPWM, spd > 0 ? spd : -spd);
      digitalWrite(motorBINA, spd > 0 ? HIGH : LOW);
      digitalWrite(motorBINB, spd > 0 ? LOW : HIGH);
      break;
    case 3:
      analogWrite(motorCPWM, spd > 0 ? spd : -spd);
      digitalWrite(motorCINA, spd > 0 ? HIGH : LOW);
      digitalWrite(motorCINB, spd > 0 ? LOW : HIGH);
      break;
    case 4:
      analogWrite(motorDPWM, spd > 0 ? spd : -spd);
      digitalWrite(motorDINA, spd > 0 ? HIGH : LOW);
      digitalWrite(motorDINB, spd > 0 ? LOW : HIGH);
      break;
  }
#else
  switch (id) {
    case 1:
      analogWrite(motorAPWM, spd > 0 ? 0 : 0);
      digitalWrite(motorAINA, spd > 0 ? HIGH : LOW);
      digitalWrite(motorAINB, spd > 0 ? LOW : HIGH);
      break;
    case 2:
      analogWrite(motorBPWM, spd > 0 ? 0 : 0);
      digitalWrite(motorBINA, spd > 0 ? HIGH : LOW);
      digitalWrite(motorBINB, spd > 0 ? LOW : HIGH);
      break;
    case 3:
      analogWrite(motorCPWM, spd > 0 ? 0 : 0);
      digitalWrite(motorCINA, spd > 0 ? HIGH : LOW);
      digitalWrite(motorCINB, spd > 0 ? LOW : HIGH);
      break;
    case 4:
      analogWrite(motorDPWM, spd > 0 ? 0 : 0);
      digitalWrite(motorDINA, spd > 0 ? HIGH : LOW);
      digitalWrite(motorDINB, spd > 0 ? LOW : HIGH);
      break;
  }
#endif
}

// void tcaselect(uint8_t i) {
// 	if (i > 7) {
// 		return;
// 	}
// 	Wire.beginTransmission(TCAADDR);
// 	Wire.write(1 << i);
// 	Wire.endTransmission();
// }


// int IR_V3() {
//   tcaselect(TCA_IR_V3);
//   int value;

//   Wire.beginTransmission(0x38 >> 1);
//   Wire.write(0x04);
//   Wire.endTransmission();
//   Wire.requestFrom(0x38 >> 1, 1);
//   value = Wire.read();

//   while (Wire.available()) {
//     Wire.read();
//   }

//   if (value > 127) {
//     value = value - 255;
//   }

//   value = value > 0? value/2 : value/2 +360;
//   if(value == 360) { value = 0;}
//   return value;
// }



// int IR_V3_strength() {
//   tcaselect(TCA_IR_V3);
//   int value;

//   Wire.beginTransmission(0x38 >> 1);
//   Wire.write(0x05);
//   Wire.endTransmission();
//   Wire.requestFrom(0x38 >> 1, 1);

//   value = Wire.read();
//   while (Wire.available()) {
//     Wire.read();
//   }

//   return 158 - value; // 158=maximum
// }




void motion(float speedA, float speedB, float speedC, float speedD) {
  motor(1, speedA * MA_OFFSET);
  motor(2, speedB * MB_OFFSET);
  motor(3, speedC * MC_OFFSET);
  motor(4, speedD * MD_OFFSET);
}

void gyroCalibration() {
  !bno.begin();
  bno.setExtCrystalUse(true);
  sensors_event_t event;
  bno.getEvent(&event);
  oldError = (float)event.orientation.x;
  if (oldError > 180) {
    oldError -= 360;
  }
}

float errorCalculation() {
  float sumD;

  sensors_event_t event;
  bno.getEvent(&event);
  error = (float)event.orientation.x;
  while (error != (float)event.orientation.x) {
    error = (float)event.orientation.x;
  }
  if (error > 180) {
    error -= 360;
  }

  //if(getBallAngle() == 0) error = 0; //didka

  sumI += error * I;
  //sumI = constrain(sumI, -50, 50);
  sumD = (oldError - error) * D;
  if (error == 0) sumI = 0;
  outPid = (error * P * (-1)) + sumI + sumD;
  oldError = error;

  //Serial.println(outPid);
  return outPid;
}

void getBallAngle() {

#pragma region didka
#define outputMin 1.0
#define outputMax 2.0
  Wire.beginTransmission(IR_I2C_ADDRESS);
  Wire.write((uint8_t)IR_REGISTER_ANGLE_AND_DISTANCE);
  Wire.endTransmission();

  Wire.requestFrom((int)IR_I2C_ADDRESS, 4);
  ballAngle = Wire.read() << 8;
  ballAngle |= Wire.read();
  ballRawDistance = Wire.read() << 8;
  ballRawDistance |= Wire.read();

  ballAngle = 180 - ballAngle;
  if (ballAngle < 0) {
    ballAngle += 360;
  }

  if (ballRawDistance < 1800) {
    ballDistanceFinalAngleOffset = 1;
  } else {
    ballDistanceFinalAngleOffset = outputMin + ((float)(ballRawDistance - ballEffectiveInputFurthes) / (ballEffectiveInputClosest - ballEffectiveInputFurthes)) * (outputMax - outputMin);
  }

  if (ballDistanceFinalAngleOffset > outputMax) ballDistanceFinalAngleOffset = outputMax;
  if (ballDistanceFinalAngleOffset < outputMin) ballDistanceFinalAngleOffset = outputMin;
    // Serial.println("Distance: " + (String)ballDistance + ", angle: " + (String)ballAngle + "°" + ", angleOffset: " + (String)ballDistanceFinalAngleOffset);

#pragma endregion didka

}

int getGoalPos() {
  int8_t numBlocks = pixy.ccc.getBlocks();
  int goalPos = 999;

  if (numBlocks > 0) {
    for (int i = 0; i < numBlocks; i++) {
      int y = pixy.ccc.blocks[i].m_y;
      int height = pixy.ccc.blocks[i].m_height;

      // Check if bottom of block is in bottom 48 pixels (roughly bottom quarter of screen)
      if ((y + height / 2) >= 108) {
        int aError = 20;
        int x = pixy.ccc.blocks[i].m_x;
        int width = pixy.ccc.blocks[i].m_width;

        int start = (x - width / 2) + aError;
        int end = (x + width / 2) - aError;

        if (end < 160) {
          goalPos = -1;
        } else if (start > 160) {
          goalPos = 1;
        } else if (start <= 160 && end >= 160) {
          goalPos = 0;
        }
        break;  // only consider the first valid block in bottom region
      }
    }
  }

  return goalPos;
}

uint16_t 
getLineAngle() {
  float lineAngle = 999;
  float xCor = 0;
  float yCor = 0;
  bool itCheck;
  itCheck = 0;
  for (int lighNumber = 0; lighNumber < 16; lighNumber++) {
    digitalWrite(multiplexerPin1, outputArray[lighNumber][0]);
    digitalWrite(multiplexerPin2, outputArray[lighNumber][1]);
    digitalWrite(multiplexerPin3, outputArray[lighNumber][2]);
    digitalWrite(multiplexerPin4, outputArray[lighNumber][3]);

    if (analogRead(multiplexerIn1) < 250) {
      itCheck = 1;
      xCor += sin(radians(lightSensorAngles[lighNumber]));
      yCor += cos(radians(lightSensorAngles[lighNumber]));
      //Serial.println(lighNumber);
    }
    if (analogRead(multiplexerIn2) < 250) {
      if (lighNumber != 12) {
        itCheck = 1;
        xCor += sin(radians(lightSensorAngles[lighNumber + 16]));
        yCor += cos(radians(lightSensorAngles[lighNumber + 16]));
        //Serial.println(lighNumber + 16);
      }
    }
  }

  if (itCheck == 1) {
    lineAngle = round((atan2(yCor, xCor) * (180 / M_PI)) + 90);

    if (lineAngle == -0) {
      lineAngle = 0;
    } else if (lineAngle < 0) {
      lineAngle += 360;
    }
    lineAngle += 180;
    if (lineAngle > 359) {
      lineAngle -= 360;
    }
  } else {
    lineAngle = 999;
  }

  // Serial.println(lineAngle);

  return lineAngle; //off    //lineAngle
}

void dribler() {
#if !STOP_MOTORS
  analogWrite(10, 255);
  digitalWrite(13, HIGH);
  digitalWrite(14, LOW);
#else
  analogWrite(10, 0);
  digitalWrite(13, HIGH);
  digitalWrite(14, LOW);
#endif
}

void kick() {
  digitalWrite(4, HIGH);
  delay(100);
  digitalWrite(4, LOW);
}

int finalAngle(float ang1) {

#pragma region didka2
#define alpha 0.05

  ballDistance = alpha * ballRawDistance + (1.0 - alpha) * ballDistance;

  int ang = floor(ang1);
  int finalAngle;

  if (ballDistance) {
    if(millis() - lineTouchTime >= 500) //advanced ball capturing time 
    {
      if(ang==0){
        finalAngle = ang;
      }else if(ang<11 && ballDistanceFinalAngleOffset>1){
        finalAngle =int (2*ang * ballDistanceFinalAngleOffset);
      }else if(ang>349 && ballDistanceFinalAngleOffset>1){
        int pomocAng=360-ang;
        int kv_finalAngle = int (2*pomocAng * ballDistanceFinalAngleOffset);
        finalAngle = 360-kv_finalAngle;
      }else if(ang<21 && ballDistanceFinalAngleOffset>1){
        finalAngle =int (2.7*ang * ballDistanceFinalAngleOffset);
      }else if(ang>339 && ballDistanceFinalAngleOffset>1){
        int pomocAng=360-ang;
        int kv_finalAngle = int (2.7*pomocAng * ballDistanceFinalAngleOffset);
        finalAngle = 360-kv_finalAngle;
      }else if (ang > 179) {
        finalAngle =int (ang / ballDistanceFinalAngleOffset);
      }else if (ang < 180) {
        int pomocAng=360-ang;
        int kv_finalAngle = int (pomocAng/ballDistanceFinalAngleOffset);
        finalAngle = 360-kv_finalAngle;
      }

    } else  //advanced ball capturing finalAngle
    { 
      if ((ballAngle < 90 || ballAngle > 270)) {
        finalAngle = ang;
       } else {
        lineTouchTime = 0;
        finalAngle = ang;
      }
    }

  // Normalize angle to 0–359
  if (finalAngle < 0) finalAngle += 360;
  if (finalAngle >= 360) finalAngle -= 360;
}
// else {
//   finalAngle = 999;
// }

// Serial.println("Angle: " + (String)ballAngle + "°" + ", angleOffset: " + (String)ballDistanceFinalAngleOffset + ", FinalAngle: " + (String)finalAngle);

#pragma endregion didka2
return finalAngle;
}

void setup() {
  pinMode(15, INPUT);  //bukaj modul

  pinMode(19, INPUT);  //switch
  pinMode(2, INPUT);

  pinMode(13, OUTPUT);  //dribler
  pinMode(14, OUTPUT);

  pinMode(4, OUTPUT);  //kicker

  pinMode(46, INPUT);  //ball detection

  define_motors();
  define_irMultiplexer();
  Serial.begin(115200);
  pixy.init();
  gyroCalibration();
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);

  kickTime = millis() - 1000;

  Wire.setClock(400000);


  Serial.println("doneeee");
}

void loop() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Push the button      to start...");
  display.display();
  //dida
  line = 180;
  oldLine = 180;

  goForward = false;
  //^dida

  if (digitalRead(19) == 0) {  //start button
    // display.clearDisplay();
    // display.setCursor(0, 0);
    // display.println("Press to STOP...");
    // display.display();
    while (digitalRead(19) == 0) {
      delay(1);
    }
    while (digitalRead(19) == 1) {
      // cycleTime = millis();
      if (digitalRead(15) != 3728) {  //bukaj module

        dribler();
        // getBallAngle();
        //didka
        oldLine = line;
        line = getLineAngle();
        if (line == 999 && oldLine != line) {
          goForward = !goForward;
          if (!goForward) {
            backwardTime = millis();
          }
        }
        //^didka
        #if DISPLAY_DEBUG
        display.clearDisplay();
        display.setTextSize(2);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(0, 0);
        display.println(lineDebug);  //line

      
        display.setTextSize(2);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(64, 0);
        display.println(getLineAngle());  //line

        display.setCursor(0, 16);
        display.println(ballAngle);

        display.setCursor(64, 16);
        // getBallAngle();
        display.println(ballRawDistance);   //finalAngle(ballAngle)
        display.display();
        #endif

        //Serial.println(line);
        errorCalculation();
        if (line == 999) {
          if (digitalRead(46) == 1) {  //dribler position7
            goForward = true;
            getBallAngle();
            int a = floor(finalAngle(ballAngle));
            //Serial.println(a);
            //Serial.println(getBallAngle());
            if (a == 999) {
              motion(0 - outPid, 0 - outPid, 0 - outPid, 0 - outPid);
            } else if ((a >= 270 and a < 344) or (a <= 90 and a > 16)) {
              motion((motionAngles[a][0] * speed * 0.7) - outPid, (motionAngles[a][1] * speed * 0.7) - outPid, (motionAngles[a][2] * speed * 0.7) - outPid, (motionAngles[a][3] * speed * 0.7) - outPid);
            } else {
              motion((motionAngles[a][0] * speed) - outPid, (motionAngles[a][1] * speed) - outPid, (motionAngles[a][2] * speed) - outPid, (motionAngles[a][3] * speed) - outPid);
            }
          } else {
            if (getGoalPos() == 0) {
              motion(0, 0, 0, 0);
              analogWrite(10, 0);  //dribler
              delay(20);

              if ((millis() - kickTime) > 1000) {
                kick();
                kickTime = millis();
              }

            } else if (getGoalPos() == 1) {
              motion(-45, -45, -45, -45);
            } else if (getGoalPos() == -1) {
              motion(45, 45, 45, 45);
              //didka
            } else {
              errorCalculation();
              if (goForward) {
                motion((motionAngles[0][0] * speed) - outPid, (motionAngles[0][1] * speed) - outPid, (motionAngles[0][2] * speed) - outPid, (motionAngles[0][3] * speed) - outPid);
              } else {
                if (millis() - backwardTime > 750) {
                  goForward = !goForward;
                }
                motion((motionAngles[180][0] * speedBack) - outPid, (motionAngles[180][1] * speedBack) - outPid, (motionAngles[180][2] * speedBack) - outPid, (motionAngles[180][3] * speedBack) - outPid);
              }
              //motion(120 - outPid, 120 - outPid, -120 - outPid, -120 - outPid);
            }
            //^didka
          }
          // Serial.println(millis() - cycleTime);

          } else {

          lineTouchTime = millis();
          line += 180;

          if (line >= 360) {
            line = line - 360;
          } else if (line <= 0) {

            line = line + 360;
          }

          lineDebug = line;


          if (digitalRead(46) == 0) {
            if (line > 90 and line < 270) {
              lineFeature = 1;
            } else {
              lineFeature = 0;
            }
  
          } else {
            lineFeature = 0;
          }
          motion((motionAngles[line][0] * maxLineSpeed) - outPid, (motionAngles[line][1] * maxLineSpeed) - outPid, (motionAngles[line][2] * maxLineSpeed) - outPid, (motionAngles[line][3] * maxLineSpeed) - outPid);
          //delay(50); //diddyCodeV2
        }
      } else {
        motion(0, 0, 0, 0);
        analogWrite(10, 0);

        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(0, 0);
        display.println("Kurva bukaj to       zastavil :(");
        display.display();
      }
    }
    while (digitalRead(19) == 0) {  //start button
      delay(1);
    }
  }

  if (digitalRead(2) == 0) {  //reset button
    while (digitalRead(2) == 0) {
      delay(1);
    }
    display.clearDisplay();

    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("Setting the          gyro...");
    display.display();
    gyroCalibration();
    delay(1000);
  }

  motion(0, 0, 0, 0);
  analogWrite(10, 0);  //dribler



  // Serial.println(millis() - cycleTime);  //line
}