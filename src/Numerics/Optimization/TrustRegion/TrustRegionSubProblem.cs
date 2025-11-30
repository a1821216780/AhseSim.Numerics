using AHSEsim.Numerics.Optimization.TrustRegion.Subproblems;

namespace AHSEsim.Numerics.Optimization.TrustRegion
{
    public static class TrustRegionSubproblem
    {
        public static ITrustRegionSubproblem DogLeg()
        {
            return new DogLegSubproblem();
        }

        public static ITrustRegionSubproblem NewtonCG()
        {
            return new NewtonCGSubproblem();
        }
    }
}
