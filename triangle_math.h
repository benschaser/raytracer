// R(t) = O + Dt origin plus direction*time
// Triangle: {V0, V1, V2}
// for intersection
// T(u, v) = (1-u-v)V0 + uV1 + vV2 for local coordinate system
// constraint: u & v >= 0
// constraint: u + v <= 1

// O + Dt = (1-u-v)V0 + uV1 + vV2

// step 1: translation
// set V0 as origin -> {V0-V0, V1-V0, V2-V0}

// step 2: scaling
// M^-1 = (-D, V1-V0, V2-V0)[t] -> M = (-D, V1-V0, V2-V1)
//                          [u] = O - V0
//                          [v]
// solve for t
// [t]                          [|T, E1, E2|]
// [u] = (1 / |(-D, E1, E2)|) * [1-D, T, E2 ]
// [v]                          [1-D, E1, T ]

// |A, B, C| = dot(-cross(A, C), B)

// [t]                             [(O-V0)xE1*E2 ]
// [u] = (1 / (cross(D, E2)*E1)) * [(DxE2)*(O-V0)]
// [v]                             [((O-V0)xE1)*D]