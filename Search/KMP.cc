#include <iomanip>
#include <iostream>
#include <random>
#include <ranges>
#include <string>
#include <vector>
/* Indexed from 1 */
std::vector<int> cache_next( const std::string& raw ) {
    std::string str( raw );
    str = " " + str;
    std::vector<int> next( str.size(), 0 );
    int len = (int)str.size();
    for ( int i : std::views::iota( 2, len ) ) {
        int pre = next[i - 1];
        while ( pre > 0 && str[pre] != str[i - 1] ) {
            pre = next[pre];
        }
        next[i] = pre + 1;
    }
    next.erase( next.begin() );
    return next;
}
/* Indexed from 0 */
std::vector<int> cache_next_0( const std::string& str ) {
    std::vector<int> next( str.size(), -1 );
    int len = (int)str.size();
    for ( int i : std::views::iota( 1, len ) ) {  // i==1 will always be 0 actually
        int pre = next[i - 1];
        while ( pre >= 0 && str[pre] != str[i - 1] ) {
            pre = next[pre];
        }
        next[i] = pre + 1;
    }
    return next;
}
/* Indexed from 0 */
std::vector<int> cache_next_0_optimize( const std::string& str ) {
    std::vector<int> next( str.size(), -1 );
    int len = (int)str.size();
    for ( int i : std::views::iota( 1, len ) ) {
        int pre = next[i - 1];
        while ( pre >= 0 && str[pre] != str[i - 1] ) {
            pre = next[pre];  // Once str[pre] == str[i - 1], all str[pre]'s next group will give this equality, as in Math deduction
        }
        next[i] = pre + 1;
        // int nTimes = 0;
        // while ( next[i] >= 0 && str[i] == str[next[i]] ) {
        if ( next[i] >= 0 && str[i] == str[next[i]] ) {  // i==1 will now be -1 if s[0],s[1] is same, such as "aa....."
            next[i] = next[next[i]];                     // This ensures all nextval is either 0 or -1 (maybe), I can't come up with a case.
            // nTimes++;
        }
        // }
        // if ( nTimes > 1 ) // This will never be true, as in Math deduction
        //     std::cout << "Narrow times: " << nTimes << std::endl;
    }
    return next;
}
int match( const std::string& str_raw, const std::string& pattern_raw, std::vector<int> const& next_raw ) {
    int s_len = (int)str_raw.size(), p_len = (int)pattern_raw.size();
    std::string str;
    std::string pattern;
    str = " " + str_raw;
    pattern = " " + pattern_raw;
    std::vector<int> next = { 0 };
    std::ranges::copy( next_raw, std::back_inserter( next ) );
    int i = 1, j = 1;
    while ( j <= p_len && i + ( p_len - j ) <= s_len ) {
        if ( j == 0 || pattern[j] == str[i] ) {
            i++;
            j++;
        } else {
            j = next[j];
        }
    }
    return j == p_len + 1 ? ( i - p_len ) : 0;
}
/* Indexed from 0 */
int match_0( const std::string& str, const std::string& pattern, std::vector<int> const& next ) {
    int p_len = (int)pattern.size(), s_len = (int)str.size(), i = 0, j = 0;
    while ( j < p_len && i + ( p_len - j ) <= s_len ) {
        if ( j == -1 || pattern[j] == str[i] ) {
            i++;
            j++;
        } else {
            j = next[j];
        }
    }
    return j == p_len ? ( i - p_len ) : -1;
}
void test( const std::string& str, const std::string& pattern ) {
    auto next = cache_next( pattern ), next_0 = cache_next_0( pattern ), next_0_optimize = cache_next_0_optimize( pattern );
    for ( int n : next ) {
        std::cout << std::setw( 3 ) << std::right << n;
    }
    std::cout << "\n";
    for ( int n : next_0 ) {
        std::cout << std::setw( 3 ) << std::right << n;
    }
    std::cout << "\n";
    for ( int n : next_0_optimize ) {
        std::cout << std::setw( 3 ) << std::right << n;
    }
    std::cout << "\n";
    std::cout << match( str, pattern, next ) << "\n";
    std::cout << match_0( str, pattern, next_0 ) << "\n";
    std::cout << match_0( str, pattern, next_0_optimize ) << "\n";
}
std::string str_gen( int len, std::mt19937& gen, int avg = 13 ) {
    std::chi_squared_distribution<double> normal( avg );
    std::string s;
    while ( len-- > 0 ) {
        int val = normal( gen );
        s.push_back( 'a' + ( val % 26 ) );
    }
    return s;
}
void rand_ins( std::string& str, const std::string& ins, std::mt19937& gen ) {
    std::uniform_int_distribution<int> u_distri( 0, str.size() );
    str.insert( u_distri( gen ), ins );
}
void random_test( std::mt19937& gen, int pattern_len, int str_len, int pattern_avg, int str_avg, const char* msg ) {
    std::cout << msg << "\n";
    std::string pattern = str_gen( pattern_len, gen, pattern_avg );
    std::string str = str_gen( str_len, gen, str_avg );
    rand_ins( str, pattern, gen );
    test( str, pattern );
}
std::string repetive_gen( size_t len, bool strong, std::mt19937& gen ) {
    std::binomial_distribution b_distri( 1, 0.7 );
    const std::string& take = str_gen( len / 10, gen, 13 );
    std::string s;
    while ( s.size() < len ) {
        int itv = b_distri( gen );
        if ( strong || itv ) {
            s += take;
            continue;
        }
        s.push_back( take[s.size() % take.size()] );
    }
    return s;
}
void repetive_test( std::mt19937& gen, bool strong, int pattern_len, int str_len, int str_avg, const char* msg ) {
    std::cout << msg << "\n";
    std::string str = str_gen( str_len, gen, str_avg );
    std::string pattern = repetive_gen( pattern_len, strong, gen );
    rand_ins( str, pattern, gen );
    test( str, pattern );
}
int main() {
    std::random_device rdv;
    std::mt19937 gen( rdv() );
    random_test( gen, 50, 100, 1, 13, "Compact pattern, loose match" );
    random_test( gen, 50, 100, 1, 3, "Compact pattern, compact match" );
    random_test( gen, 50, 100, 13, 13, "Lose pattern, loose match" );
    repetive_test( gen, false, 60, 100, 13, "Repetive pattern" );
    repetive_test( gen, true, 60, 100, 13, "Strong repetive pattern" );
}
