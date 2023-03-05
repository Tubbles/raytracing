#pragma once

#define INTERFACE(name)                                                                                                \
    name() = default;                               /* Cannot use parens here, NOLINT(bugprone-macro-parentheses) */   \
    name(const name &) = default;                   /* Cannot use parens here, NOLINT(bugprone-macro-parentheses) */   \
    name(name &&) = default;                        /* Cannot use parens here, NOLINT(bugprone-macro-parentheses) */   \
    auto operator=(const name &)->name & = default; /* Cannot use parens here, NOLINT(bugprone-macro-parentheses) */   \
    auto operator=(name &&)->name & = default;      /* Cannot use parens here, NOLINT(bugprone-macro-parentheses) */   \
    virtual ~name() = default                       /* Cannot use parens here, NOLINT(bugprone-macro-parentheses) */
