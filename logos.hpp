#pragma once
const char* logo_arch =
"\033[36m                   -`                 \033[0m\n"
"\033[36m                  .o+`                \033[0m\n"
"\033[36m                 `ooo/                \033[0m\n"
"\033[36m                `+oooo:               \033[0m\n"
"\033[36m               `+oooooo:              \033[0m\n"
"\033[36m               -+oooooo+:             \033[0m\n"
"\033[36m             `/:-:++oooo+:            \033[0m\n"
"\033[36m            `/++++/+++++++:           \033[0m\n"
"\033[36m           `/++++++++++++++:          \033[0m\n"
"\033[36m          `/+++ooooooooooooo/`        \033[0m\n"
"\033[36m         ./ooosssso++osssssso+`       \033[0m\n"
"\033[36m        .oossssso-````/ossssss+`      \033[0m\n"
"\033[36m       -osssssso.      :ssssssso.     \033[0m\n"
"\033[36m      :osssssss/        osssso+++.    \033[0m\n"
"\033[36m     /ossssssss/        +ssssooo/-    \033[0m\n"
"\033[36m   `/ossssso+/:-        -:/+osssso+-  \033[0m\n"
"\033[36m  `+sso+:-`                 `.-/+oso: \033[0m\n"
"\033[36m `++:.                           `-/+/ \033[0m\n"
"\033[36m .`                                 `/ \033[0m\n";

const char* logo_debian =
"\033[31m       _,met$$$$$gg.       \033[0m\n"
"\033[31m    ,g$$$$$$$$$$$$$$$P.    \033[0m\n"
"\033[31m  ,g$$P\"\"       \"\"\"Y$$.\".  \033[0m\n"
"\033[31m ,$$P'              `$$$. \033[0m\n"
"\033[31m',$$P       ,ggs.     `$$b:\033[0m\n"
"\033[31m`d$$'     ,$P\"'   .    $$$\033[0m\n"
"\033[31m $$P      d$'     ,    $$P\033[0m\n"
"\033[31m $$:      $$.   -    ,d$$'\033[0m\n"
"\033[31m $$;      Y$b._   _,d$P'  \033[0m\n"
"\033[31m Y$$.    `.`\"Y$$$$P\"'     \033[0m\n"
"\033[31m `$$b      \"-.__          \033[0m\n"
"\033[31m  `Y$$                     \033[0m\n"
"\033[31m   `Y$$.                   \033[0m\n"
"\033[31m     `$$b.                 \033[0m\n"
"\033[31m       `Y$$b.              \033[0m\n"
"\033[31m          `\"Y$b._          \033[0m\n"
"\033[31m              `\"\"\"         \033[0m\n";

const char* logo_ubuntu =
"\033[37m                  $2.',:clooo:  \033[31m.:looooo:.\033[0m\n"
"\033[37m           ;looooooooc  \033[31m.oooooooooo'\033[0m\n"
"\033[37m        ;looooool:,''.  \033[31m:ooooooooooc\033[0m\n"
"\033[37m       ;looool;.         \033[31m'oooooooooo,\033[0m\n"
"\033[37m      ;clool'             \033[31m.cooooooc.  \033[37m,,\033[0m\n"
"\033[37m         ...                \033[31m......  \033[37m.:oo,\033[0m\n"
"\033[31m  ;clol:,.                        \033[37m.loooo'\033[0m\n"
"\033[31m :ooooooooo,                        \033[37m'ooool\033[0m\n"
"\033[31m'ooooooooooo.                        \033[37mloooo.\033[0m\n"
"\033[31m'ooooooooool                         \033[37mcoooo.\033[0m\n"
"\033[31m ,loooooooc.                        \033[37m.loooo.\033[0m\n"
"\033[31m   .,;;;'.                          \033[37m;ooooc\033[0m\n"
"\033[37m       ...                         ,ooool.\033[0m\n"
"\033[37m    .cooooc.              \033[31m..',,'.  \033[37m.cooo.\033[0m\n"
"\033[37m      ;ooooo:.           \033[31m;oooooooc.  \033[37m:l.\033[0m\n"
"\033[37m       .coooooc,..      \033[31mcoooooooooo.\033[0m\n"
"\033[37m         :ooooooolc:. \033[31m.ooooooooooo'\033[0m\n"
"\033[37m           ':loooooo;  \033[31m,oooooooooc\033[0m\n"
"\033[37m               ..';::c'  \033[31m.;loooo:'\033[0m\n";

// -----------------------------
// Logo mapping
// -----------------------------
std::string get_logo(const std::string& distro) {
    if (distro.find("Arch") != std::string::npos) {
        return logo_arch;
    }
    if (distro.find("Debian") != std::string::npos) {
        return logo_debian;
    }
    if (distro.find("Ubuntu") != std::string::npos) {
        return logo_ubuntu;
    }
    return ""; // nothing if not recognized
}
