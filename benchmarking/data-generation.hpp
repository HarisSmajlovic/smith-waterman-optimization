/**
 * A small application to generate random input vectors for benchmarking tests.
 */

#include <random> 	// std::rand, std::srand, std::default_random_engine

namespace csc586 {
namespace benchmark {

/**
 * Creates and returns a vector pre-populated by repeatedly calling gen size times.
 *
 * see timing.hpp for a description of functors (e.g., gen). size_t is the built-in
 * type that refers to the size of things. On most architectures, it is a 64-bit
 * unsigned integer.
 *
 * Note the use of auto with a trailing return type. This can be a useful pattern
 * when the return type depends on a generic input parameter.
 */
template < typename RandomGenerator >
	auto build_rand_vec( RandomGenerator gen, size_t const size )
        -> std::vector< decltype((gen)()) >
	{
		// see timing.hpp for a description of decltype().
		// Initialises a vector with the appropriate size, in which we will create the random data.
		std::vector< decltype((gen)()) > random_data( size );

		// std::generate() = STL. This could be done with a loop from 0,...,size, calling gen() each
		// iteration. See https://www.fluentcpp.com/2017/01/05/the-importance-of-knowing-stl-algorithms/
		// for a compelling discussion of why using STL algorithms like this is better than explicit loops.
		// Spoiler: it better self-documents (in code) intent and is less prone to off-by-one-errors.
		// For an explanation of syntax, see the use of std::for_each() in timing.hpp
		std::generate( random_data.begin(), random_data.end(), gen );

		return random_data;
	}


std::string random_string( size_t length )
{
    auto randchar = []() -> char
    {
        const char charset[] =
        "ACGT";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[ std::rand() % max_index ];
    };
    std::string str(length,0);
    std::generate_n( str.begin(), length, randchar );
    return str;
}


// Vector of length n, each string is length m
std::pair<std::string, std::string> random_vector_pair_gen(size_t const m) {
	std::pair <std::string, std::string> foo;
	foo = std::make_pair(random_string(m), random_string(m));
	return foo;
}

/**
 * Builds a vector of pairs of strings of random primitive values of type T
 */
template < typename T >
    auto uniform_rand_vec_of_vec( size_t const n, size_t const m )
        -> std::vector< std::pair< T,T > >
    {
				
        return build_rand_vec( [ m ](){
            return random_vector_pair_gen( m ); }
            , n );
    }


} // namespace benchmark
} // namespace csc586
