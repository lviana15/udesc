import { Prisma } from '@prisma/client'
import { Decimal } from 'decimal.js'

function convertDecimalToNumber(obj: any): any {
    if (obj === null || obj === undefined) return obj

    if (obj instanceof Decimal) {
        return obj.toNumber()
    } else if (Array.isArray(obj)) {
        return obj.map(convertDecimalToNumber)
    } else if (typeof obj === 'object') {
        for (const key in obj) {
            obj[key] = convertDecimalToNumber(obj[key])
        }
    }
    return obj
}

export function decimalMiddleware() {
    return async (params: Prisma.MiddlewareParams, next: (params: Prisma.MiddlewareParams) => Promise<any>) => {
        const result = await next(params)
        return convertDecimalToNumber(result)
    };
}

