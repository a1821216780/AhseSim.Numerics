using AHSEsim.Numerics.LinearAlgebra;

namespace AHSEsim.Numerics.Optimization.TrustRegion
{
    public interface ITrustRegionSubproblem
    {
        Vector<double> Pstep { get; }
        bool HitBoundary { get; }

        void Solve(IObjectiveModel objective, double radius);
    }
}
